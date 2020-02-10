/**********************\
|     ASSIGNMENT 1     |
|   Emre REYHANLIOÐLU  |
|      150140126       |
\**********************/

#include <stdio.h>

int main(void)
{
	int  ZellersResult = 0 , year=0, copyOfYear=0 , q=0, m=0, j=0, k=0 , endYear = 0, numberOfMatch = 0 ,
	 numberOfStep, iterYear=0 , iter=0 , i=0 , Result=0;


		printf("Enter date [year month day]: ");
		scanf("%d%d%d", &year,&m,&q);
		copyOfYear = year;

		if(year<1000 || year>9999)	//Checking input year
		{
			printf("Invalid date.\n");
			return 1;
		}
		//Checking input for months that has 31 days
		else if( m>12 || m<1 || ((m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) && ( q>31 || q<1)) )
		{
			printf("Invalid date.\n");
			return 1;
		}
		//Checking input for months that has 30 days
		else if( ( ( m==4 || m==6 || m==9 || m==11) && ( q>30 || q<1)) )
		{
			printf("Invalid date.\n");
			return 1;
		}
		//Checking input for february
		else if(m==2 && (q>28 || q<1))
		{
			printf("Invalid date.\n");
			return 1;
		}


		printf("Enter end year: ");
		scanf("%d", &endYear);
		if(endYear <= year)
		{
			printf("Invalid end date.\n");
			return 1;
		}

	j = year/100;
	k = year%100;

	if( m == 1 || m == 2)
	{
		m += 12; year --; iterYear = year+1;
	}
	else iterYear = year;

	j = year/100;  k = year%100;

	ZellersResult = (q + (13*(m+1)/5) + k + k/4 + j/4 + 5*j) %7;

	switch ( ZellersResult)
	{
		case 0:
			printf("Is's a Saturday.\n");
			break;
		case 1:
			printf("It's a Sunday.\n");
			break;
		case 2:
			printf("It's a Monday.\n");
			break;
		case 3:
			printf("It's a Tuesday.\n");
			break;
		case 4:
			printf("It's a Wednesday.\n");
			break;
		case 5:
			printf("It's a Thursday.\n");
			break;
		case 6:
			printf("It's a Friday.\n");
			break;
	}

	iterYear++;
	numberOfStep = endYear - iterYear +1 ;

	for( i = 0 ; i< numberOfStep; i++ , iterYear++)
	{
		iter = iterYear;

		if( m == 1 || m == 2)
		{
			m += 12; iter --;
		}

		j = iter/100;  k = iter%100;

		Result = (q + (13*(m+1)/5) + 5*k/4 + j/4 + 5*j) %7;

		if ( ZellersResult == Result )
			numberOfMatch++;

		if(m>12)
			m -=12;
	}

	printf("Same day-and-month on same weekday between %d and %d: %d\n", copyOfYear+1 , endYear , numberOfMatch);

	return 0;
}


