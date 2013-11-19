/* Includes */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>


pthread_mutex_t *fourchettes;
pthread_t *philosophes;

int nombre_philosophes;

void* activite_philo(void* arg)
{

	int right=0;
	int left=0;


	int philoPos = (int)(long int)arg;

	int gauche = philoPos;
	int droite = philoPos - 1;
	if(droite == -1)
	{
		droite = nombre_philosophes-1;
	}

	while(1)
	{
		// printf("%d: j'ai faim\n",philoPos);
		if(right == 0)
		{	

			printf("%d: je veux ma fourchette droite: %d\n",philoPos,droite);
			pthread_mutex_lock(&fourchettes[droite]);	
			right = 1;	
			printf("%d: j'ai ma fourchette droite: %d\n",philoPos, droite);
			sleep(3);
		}
		if(left == 0)
		{
			printf("%d: je veux ma fourchette gauche: %d\n",philoPos,gauche);
			int try = pthread_mutex_trylock(&fourchettes[gauche]);
			if(try != 0)
			{
				if (right == 1)
				{
					pthread_mutex_unlock(&fourchettes[droite]);
					right = 0;
					printf("%d: j'ai laché ma fourchette droite parce que l'autre était prise: %d\n",philoPos, droite);
					sleep(3);
				}
			}
			else
			{			
				left = 1;
				printf("%d: j'ai ma fourchette gauche: %d\n",philoPos,gauche);
				sleep(3);
			}
		}

		if ((left ==1) && (right == 1))
		{
			// Si droite et gauche avec couverts alors miam puis dodo
			printf("%d: j'ai mes deux fourchettes! miam!\n",philoPos);
			sleep(5);
		
			// puis je lache mes fourchettes
			printf("%d: je lache ma fourchette droite: %d\n",philoPos,droite);
			pthread_mutex_unlock(&fourchettes[droite]);
			right = 0;
			printf("%d: j'ai lache' ma fourchette droite: %d\n",philoPos, droite);
			sleep(3);
	

			printf("%d: je lache ma fourchette gauche: %d\n",philoPos,gauche);	
			pthread_mutex_unlock(&fourchettes[gauche]);
			left = 0;
			printf("%d: j'ai lache' ma fourchette droite: %d\n",philoPos, gauche);
			sleep(3);
		}
	}

	return NULL ; // dummy
}



int main()
{
	nombre_philosophes = 5;

	//allocating memory
	philosophes = calloc(5, sizeof(pthread_t));
	fourchettes = calloc(5,sizeof(pthread_mutex_t));

	int i;
	for(i=0;i<5;i++)
	{
		//initializing mutexes		
		int merror = pthread_mutex_init(&fourchettes[i],NULL);
		if(merror != 0)
		{
			printf("mutex init error %d\n", i);
		}
	}

	for(i=0;i<5;i++)
	{
		//initializing threads
		int terror = pthread_create(&philosophes[i], NULL,activite_philo, (void*)(long int)i);
		if (terror != 0)
		{
			printf ("thread create error %d\n", i);
		}

		
	}


	for(;;);
}
