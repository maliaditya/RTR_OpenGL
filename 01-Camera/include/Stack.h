#pragma once
#define MAX_SIZE 32

using namespace vmath;

mat4 transformationStack[MAX_SIZE];
int top = -1;

bool isEmpty(void) 
{

	if (top == -1)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool isFull(void) 
{

	if (top == MAX_SIZE-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void pushMatrix(mat4 matrix)
{
	if (isFull()==false)
	{
		top = top + 1;
		transformationStack[top] = matrix;
	}

}

mat4 popMatrix(void)
{

		mat4 matrix = transformationStack[top];
		top = top - 1;
		return matrix;
	
}

