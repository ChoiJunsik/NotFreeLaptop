#pragma once

#include "stdafx.h"
static BOOL Encrypt(char* source, char* destination, DWORD length);
static BOOL Decrypt(char* source, char* destination, DWORD length);

BOOL Encrypt(char *source, char *destination, DWORD length)

{

	const int C1 = 52845;
	const int C2 = 22719;
	const int KEY = 78695;


	DWORD i;
	int key = KEY;
	if (!source || !destination || length <= 0)
	{
		return FALSE;
	}
	for (i = 0; i<length; i++)
	{
		destination[i] = source[i] ^ key >> 8;
		key = (destination[i] + key) * C1 + C2;
	}
	return TRUE;
}
BOOL Decrypt(char *source, char *destination, DWORD length)
{


	const int C1 = 52845;
	const int C2 = 22719;
	const int KEY = 78695;

	DWORD i;
	char previousBlock;
	int key = KEY;
	if (!source || !destination || length <= 0)
	{
		return FALSE;
	}
	for (i = 0; i<length; i++)
	{
		previousBlock = source[i];
		destination[i] = source[i] ^ key >> 8;
		key = (previousBlock + key) * C1 + C2;
	}
	return TRUE;
}