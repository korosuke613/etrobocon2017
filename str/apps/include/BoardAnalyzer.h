#ifndef _INC_BOARD_ANALYZER
#define _INC_BOARD_ANALYZER

class BoardAnalyzer
{
public:
	BoardAnalyzer();
	~BoardAnalyzer();
	void set(int* initPositions);
	int getInLeftSquareCount();
	bool getExchangePattern();
	
private:
	int *positions;
	const int leftSquare[5] = {0, 1, 5, 2, 10};

};

#endif //_INC_BOARD_ANALYZER