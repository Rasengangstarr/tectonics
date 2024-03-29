#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <cfloat>

using namespace std;

const int x = 100;
const int y = 25;
const int num_heat_centroids = 1;
const float down_coef = 0.9;
const float split_coef = 1;
const float lat_coef = 0.2;
const float up_coef = 0.1;

int main()
{
	//Random Seed
	srand(time(NULL));	
	
	//Instantialise the Soup and the Core
	float soup[x*y] = { };

	for (int i = 0; i < x*y; i++)
	{
		//soup[i] = 1;
	}

	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 90000000L;

	float core[x] = { 0 };
	int centroids[num_heat_centroids];
	int inputBin;
	for (int i = 0; i < num_heat_centroids; i++)
	{
		int centroid = rand() % x;
		centroids[i] = 50;
	}
	for (int i = 0; i < num_heat_centroids; i++)
	{
		//if (core[centroids[i]] < 10)	
		//{
			core[centroids[i]] += 1000000;
		//}
	}

	while (true)
	{
		//handle heat dissipation in the core
		for (int i = 0; i < x; i++)
		{
			if (i > 0)
			{
				float transferLeft = (lat_coef/1) * 1 * (core[i] - core[i-1]);
				core[i] -= transferLeft;
				core[i-1] += transferLeft;
			}
			if (i < x) 
			{
				float transferRight = (lat_coef/1) * 1 * (core[i] - core[i+1]) ;
				core[i] -= transferRight;
				core[i+1] += transferRight;
			}

			float transferDown = (down_coef/1) * 1 * (core[i] - soup[i]);
			core[i] -= transferDown;
			soup[i] += transferDown;
		}

		//handle heat dissipation in the mantle
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				//tranfer heat
				if (soup[i * x + j] > 1 && j >= 0 && j < x - 1)
				{	
					if (i == y - 1)
					{
						soup[(i * x + j)] = 1;
						continue;
					}

					
					if (soup[((i+1) * x + j)] < 100)
					{	
						float transferDown = (down_coef/1) * 1 * (soup[(i * x + j)] - soup[((i+1) * x + j)]);
						soup[(i * x + j)] -= transferDown;
						soup[((i+1) * x + j)] += transferDown;
					}
					if (i >= 0 || soup[((i-1) * x + j)] < 100)
					{
						float transferUp = (up_coef/1) * 1 * (soup[(i * x + j)] - soup[((i-1) * x + j)]);
						soup[(i * x + j)] -= transferUp;
						soup[((i-1) * x + j)] += transferUp;
					}
					float transferLeft;
					float transferRight;
				 	
				        if (soup[(i * x + j - 1)] < 100)
					{	
						transferLeft = (lat_coef/1) * 1 * (soup[(i * x + j)] - soup[(i * x + j - 1)]);
						soup[(i * x + j)] -= transferLeft;
						soup[(i * x + j - 1)] += transferLeft;
					}
					if (soup[(i * x + j + 1)] < 100)
					{
						transferRight = (lat_coef/1) * 1 * (soup[(i * x + j)] - soup[(i * x + j + 1)]);
						soup[(i * x + j)] -= transferRight;
						soup[(i * x + j + 1)] += transferRight;
					}
					//cout << i << " " << j << " " << transferDown << " " << soup[i + x * j] << " " << soup[(i+1) * x + j] << endl;
				}

			}
		}

		
		for (int i = 0; i < x; i++)
		{
			if ((int)core[i]/10 > 9)
				cout << 9;
			else
				cout << (int)core[i]/10;
		}
		cout << endl;
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				if ((int)(soup[i * x + j] / 10) > 9)
					cout << 9;
			        else	
					cout << (int)(soup[i * x + j] / 10);
			}
			cout << endl;
		}
		cout << endl;
		nanosleep(&tim, &tim2);
		system("clear");
	}

}
