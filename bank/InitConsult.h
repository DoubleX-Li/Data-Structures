void MinusC(int rconsult[], int x)
{
	int n;
	if(rconsult[x] > 5)
		rconsult[x]--;
	else
	{
		n = rand() % 100;
		MinusC(rconsult,n);
	}
}

void PlusC(int rconsult[], int x)
{
	int n;
	if(rconsult[x] < 60)
		rconsult[x]++;
	else
	{
		n = rand() % 100;
		PlusC(rconsult,n);
	}
}

void InitC(int rconsult[])
{
	int i;
	for(i = 0; i < 100; i++)
	{
		rconsult[i] = 10;
	}
}

void ShowConsult(int rconsult[])
{
	int sum = 0;
	for(int i = 0; i < MAX; i++)
	{
		if(i != 0 && i % 10 == 0)
			std::cout << std::endl;
		std::cout << std::setw(2) << rconsult[i] << " ";
		sum += rconsult[i];
	}
	std::cout << "\nConsult sum = "<< sum / MAX << std::endl;
}

void InitConsult(int rconsult[])
{
	int i = 10000;
	int x;
	
	InitC(rconsult);
	srand(time(NULL));
	while(i--)
	{
		x = rand() % 100;
		MinusC(rconsult,x);
		x = rand() % 100;
		PlusC(rconsult,x);
	}
} 
