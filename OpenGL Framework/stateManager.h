class StateManagerC
{
public:
	enum STATES
	{
		TITLE_SCREEN,
		SPACE
	};

	static StateManagerC	*CreateInstance();
	static StateManagerC	*GetInstance() {return sInstance;};
	~StateManagerC(){};
	
	int32_t		getState();
	void		setState(int32_t stateToSet);
	void		shutdown();
private:
	static StateManagerC *sInstance;
	StateManagerC(){};
	int32_t		mCurrentState;
};