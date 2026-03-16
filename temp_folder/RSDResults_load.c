#include "sources/RAiSD.h"

void RSDResults_load(RSDResults_t *RSDResults, RSDCommandLine_t *RSDCommandLine)
{
	if (RSDResults == NULL)
		return;

	assert(RSDCommandLine != NULL);

	char reportPath[STRING_SIZE], rline[STRING_SIZE];

	strncpy(reportPath, "tempOutputFolder/PredResults.txt", STRING_SIZE);

	FILE *fp = fopen(reportPath, "r");
	assert(fp != NULL);

	int setIndex = -1, gridPointIndex = -1, gridPointDataIndex = -1;

	while (fgets(rline, STRING_SIZE, fp) != NULL)
	{
		char *imgName = strtok(rline, " ");
		char *imgClass = strtok(NULL, " ");
		assert(imgClass != NULL);

		char *imgProb0 = strtok(NULL, " "); // class 0
		assert(imgProb0 != NULL);
		char *imgProb1 = strtok(NULL, " "); // class 1

		getIndicesFromImageName(imgName, &setIndex, &gridPointIndex, &gridPointDataIndex);

		RSDGridPoint_t *RSDGridPoint = RSDResults->gridPointData[setIndex * RSDResults->setGridSize + gridPointIndex];

		int positiveClassIndex = RSDCommandLine->positiveClassIndex[0];

		RSDGridPoint->nnPositiveClass0[gridPointDataIndex] = positiveClassIndex == 0 ? (float)atof(imgProb0) : (float)atof(imgProb1);
		assert(RSDGridPoint->nnPositiveClass0[gridPointDataIndex] >= 0.0 && RSDGridPoint->nnPositiveClass0[gridPointDataIndex] <= 1.0);

		RSDGridPoint->nnPositiveClass0[gridPointDataIndex] = (RSDGridPoint->nnPositiveClass0[gridPointDataIndex] < THRESHOLD) ? (int)0 : (int)1; // Threshold calculation
		assert(RSDGridPoint->nnPositiveClass0[gridPointDataIndex] == 0 || RSDGridPoint->nnPositiveClass0[gridPointDataIndex] == 1);				 // Threshold output assertion

		RSDGridPoint_calcCompositeScore(RSDGridPoint, gridPointDataIndex); // stores in nnPositiveClass1
	}

	fclose(fp);

	exec_command("rm -r tempOutputFolder");
}

void RSDResults_load(RSDResults_t *RSDResults, RSDCommandLine_t *RSDCommandLine)
{
	if (RSDResults == NULL)
		return;

	assert(RSDCommandLine != NULL);

	char reportPath[STRING_SIZE], rline[STRING_SIZE];

	FILE *fp = fopen(reportPath, "r");
	assert(fp != NULL);

	int setIndex = -1, gridPointIndex = -1, gridPointDataIndex = -1;
}