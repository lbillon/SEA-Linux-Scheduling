/* Includes */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>


struct pthTable
{
	pthread_t id;
	int pthread_num;
	int right;
	int left;
};
struct couverts
{
	pthread_mutex_t fourchette;
	int mutex_num;
};


struct pthTable* tInfo;	
struct couverts* tiroir;


void* activite_philo(void* arg)
{
struct pthTable* localInfo = arg;
int philoPos = localInfo->pthread_num;	
printf("j'ai la position %d\n",philoPos);
	if(localInfo->right == 0)
	{	
		
		if (philoPos == 1)
		{
			pthread_mutex_lock(&(tiroir[4].fourchette));
			localInfo->right = 1;
			printf("j'ai la fourchette de droite et je suis %d\n",philoPos);
			sleep(3);
		}
		else{
			pthread_mutex_lock(&(tiroir[philoPos-1].fourchette));
			localInfo->right = 1;
			printf("j'ai la fourchette de droite et je suis %d\n",philoPos);
			sleep(3);
		}
	}
	if(localInfo->left == 0)
	{
		pthread_mutex_lock(&(tiroir[philoPos].fourchette));
		localInfo->left = 1;
		printf("j'ai la fourchette de gauche et je suis %d\n",philoPos);
		sleep(3);
	}
	// Si droite et gauche avec couverts alors dodo
	printf("j'ai mes deux fourchettes! miam! je suis %d\n",philoPos);
	sleep(5);
	
	//unlock dabord gauche et puis droite
	pthread_mutex_unlock(&(tiroir[philoPos].fourchette));
	localInfo->left = 0;
	printf("je lache la fourchette de gauche et je suis %d\n",philoPos);
	if (philoPos == 1)
		{
			pthread_mutex_unlock(&(tiroir[5].fourchette));
			localInfo->right = 0;
			printf("je lache la fourchette de droite et je suis %d\n",philoPos);
			sleep(3);
		}
		else{
			pthread_mutex_unlock(&(tiroir[philoPos-1].fourchette));
			localInfo->right = 0;
			printf("je lache la fourchette de droite et je suis %d\n",philoPos);
			sleep(3);
		}
}


int main()
{


	//allocating memory
	tInfo = calloc(5, sizeof(struct pthTable));
	tiroir = calloc(5, sizeof(struct couverts));
	int i;
	for(i=0;i<5;i++)
	{
		//initializing threads
		tInfo[i].pthread_num = i+1;
		printf("num: %d\n",tInfo[i].pthread_num);
		int terror = pthread_create(&tInfo[i].id, NULL,activite_philo, &tInfo[i]);
		if (terror != 0)
		{
			printf ("thread create error %d\n", tInfo[i].pthread_num);
		}
		tInfo[i].right = 0;
		tInfo[i].left = 0;

		//initializing mutexes		
		tiroir[i].mutex_num = i+1;		
		int merror = pthread_mutex_init(&(tiroir[i].fourchette),NULL);
		if(merror != 0)
		{
			printf("mutex init error %d\n", tiroir[i].mutex_num);
		}
	}


	for(;;);
}
