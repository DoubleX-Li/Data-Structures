void MinusA(int rarrive[], int x)
{
	int n;
	if(rarrive[x] > 0)
		rarrive[x]--;
	else
	{
		n = rand() % 100;
		MinusA(rarrive,n);
	}
}

void PlusA(int rarrive[], int x)
{
	int n;
	if(rarrive[x] < 20)
		rarrive[x]++;
	else
	{
		n = rand() % 100;
		PlusA(rarrive,n);
	}
}

void InitA(int rarrive[])
{
	int i;
	for(i = 0; i < 100; i++)
	{
		rarrive[i] = 4;
	}
}

void ShowArrive(int rarrive[])
{
	int sum = 0;
	for(int i = 0; i < MAX; i++)
	{
		if(i != 0 && i % 10 == 0)
			std::cout << std::endl;
		std::cout << std::setw(2) << rarrive[i] << " ";
		sum += rarrive[i];
	}
	std::cout << "\nArrive sum = "<< sum / MAX <<std::endl;
}

void InitArrive(int rarrive[])
{
	int i = 10000;
	int x;
	
	InitA(rarrive);
	srand(time(NULL));
	while(i--)
	{
		x = rand() % 100;
		MinusA(rarrive,x);
		x = rand() % 100;
		PlusA(rarrive,x);
	}
} 
