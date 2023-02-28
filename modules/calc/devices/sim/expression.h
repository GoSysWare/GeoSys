#ifndef DEVICES_SIM_EXPRESSION_H__
#define DEVICES_SIM_EXPRESSION_H__

#include<string>


// Tree evaluation variables

#define DIVISION_BY_0 1
#define ILEGAL_OPERATION 2
#define UNDEFINED_VARIABLE 3
#define INVALID_DOMAIN 4



/////////////////////////////////////////////////////////////////////////////

class  CExpression
{

public:
	CExpression &operator=(CExpression& expr);
	CExpression(CExpression & expresie);
	
	struct nod 
	{
		struct nod *left,*right;
		unsigned char operatie; 
		union { 
			double valoare;
			void * pvObj;
		};
	};
	
	typedef nod NOD;
	typedef nod *arbore;
	
	arbore CloneTree(void);
	int UpdateArbore(void);		// Update the tree
	arbore GetArbore();
	int Value(double & valoare);	// gets the value of the expression
	int ChangeExpression(std::string & expresie);	// Change expression
	
	CExpression();
	virtual ~CExpression();

private:
	// Error code var
	int error_code;
	arbore sgOp();
	arbore logicalOp();
	void SkipSpaces();
	std::string  m_definitie;			// the expression in string
	int pozitie;					// string parsing variable
	arbore m_Arbore;				// the expresion as a binary tree
	
	double vexp ( arbore a );
	arbore factor (void);			// the partial expresion parsing functions
	arbore identificator(void);
	arbore putere(void);
	arbore termen(void);
	arbore expresie(void);
	void elibmem ( arbore a);
	arbore clone(arbore arb);
};

 bool  evaluate(const std::string text, double * val);

#endif 