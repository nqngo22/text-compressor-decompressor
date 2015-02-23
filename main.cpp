#include <iostream>
#include <cstdlib>
#include <string>
#include "minheap.h"
//#include <istream>
#include <cstring>
//#include <algorithm>

using namespace std;

void Huffman(cMinHeap& H, int n)
{
    if(n < 2);
    else
    {
        for(int i = 0; i < n - 1; ++i)
        {
            sNode* first = new sNode;
            sNode* second = new sNode;
            first = H.Pop();
            second = H.Pop();
            sNode bt;
            bt.frequency = first->frequency + second->frequency;

            if(first->frequency < second->frequency)
            {
                bt.right = first; bt.left = second;
            }
            else if(first->frequency == second->frequency)
            {
                if(first->asciivalue < second->asciivalue)
                    { bt.right = first; bt.left = second;}
                else if(second->asciivalue < first->asciivalue)
                    { bt.right = second; bt.left = first;}
            }
            else
                { bt.right = second; bt.left = first;}

            if(first->asciivalue < second->asciivalue)
                bt.asciivalue = first->asciivalue;
            else if(second->asciivalue < first->asciivalue)
                bt.asciivalue = second->asciivalue;

            H.Push(bt);
        }
    }
}


string convertbinary(int x)
{
	string s;
	for(int i = 0; i < 8; ++i)
	{
	  	s.push_back('0' + (x & 1));
		x >>= 1;
	}
	//reverse(s.begin(), s.end());
	return s;
}


int main(int argc, char * argv[])
{
    if(argc == 2 && strcmp(argv[1],"-d") == 0)
    {
        char ascii[256][4];
        cMinHeap minheap(10);

        cin.read(ascii[0], 4);
        cin.read(ascii[0], 4);
        for(int i = 0; i < 256; ++i)
            cin.read(ascii[i], 4);

        sNode asciiarray[256];
	char* p;
	int totalfrequency = 0;
        for(int i = 0; i < 256; ++i)
        {
            asciiarray[i].frequency = *((int*) ascii[i]);
	    totalfrequency += asciiarray[i].frequency;
            asciiarray[i].asciivalue = i;
            //cout << i << " " << asciiarray[i].frequency << endl;
            //cout << char(strtol(ascii[i], &p, 2));
        }

        int numchars = 0;
        for(int i = 0; i < 256; ++i)
        {
            if(asciiarray[i].frequency > 0)
            {
                minheap.Push(asciiarray[i]);
                numchars++;
            }
        }

        Huffman(minheap, minheap.heapsize);
        sCharacter characters[numchars];
        int index = 0;
        int counter = 0;

        minheap.append(minheap.heap[1], characters, 5, index, counter);





        string binary;
	char c;
	while(cin.get(c))
		binary.append(1,c);
	//cout << binary;
	char* pEnd;
	string rbinary;

	//cout << binary[0];

	for(int i = 0; i < binary.length(); ++i)
	{	//char c = binary[i];
		int temp = binary[i];
		rbinary.append(convertbinary(temp));
	}
	//cout << rbinary;
	sNode a =  minheap.heap[1];

	int index2 = 0;
	//while(index2 < rbinary.length())
	//	 decode(minheap.heap[1], pRoot, rbinary, index2);
	int fcounter = 0;
	while(index2 < rbinary.length() && fcounter < totalfrequency)
	{
		if(rbinary[index2] == '0')
		{
			a = *a.left;
			if(a.left == NULL)
			{
				cout << char(a.asciivalue);
				++fcounter;
				a = minheap.heap[1];
			}
			index2++;
		}
		else if(rbinary[index2] == '1')
		{
			a = *a.right;
			if(a.left == NULL)
			{
				cout << char(a.asciivalue);
				++fcounter;
				a = minheap.heap[1];
			}
			index2++;
		}
	}

    }
    else
    {
        sNode asciiarray[256];
        cMinHeap minheap(10);
        int numchars = 0;

        for(int i = 0; i < 256; ++i)
            asciiarray[i].asciivalue = i;

        char c;
        unsigned char x;
        while(cin.get(c))
        {
            x = (unsigned char)c;
            asciiarray[int(x)].frequency++;
        }

        cin.clear();
        cin.seekg(0,cin.end);
        int length = cin.tellg();
        cin.seekg(0,cin.beg);
        char input[length];
        cin.read(input, length);

        for(int i = 0; i < 256; ++i)
        {
            if(asciiarray[i].frequency > 0)
            {
                minheap.Push(asciiarray[i]);
                numchars++;
            }
        }
        int uniqueletters = minheap.heapsize;
        Huffman(minheap, minheap.heapsize);
        sCharacter characters[numchars];
        int index = 0;
        int counter = 0;

        minheap.append(minheap.heap[1], characters, 5, index, counter);

        cout << "HUFFMA5";
        cout << '\0';
        for(int i = 0; i < 256; ++i)
        {
          int a = asciiarray[i].frequency;
          char *p = (char*)&a;
          for(int j = 0; j < 4; ++j)
             cout << *p++;
        }

        if(uniqueletters > 1)
        {
            sCharacter characters2[256];
            for(int i = 0; i < numchars; ++i)
            characters2[characters[i].ascii] = characters[i];
            string binary;

            for(int i = 0; i < length; ++i)
            {
                x = (unsigned char)input[i];
                binary.append(characters2[int(x)].binary);
            }

            if(binary.length() % 8 != 0)
            {
                int padd =  (8 - (binary.length() % 8));
                for(int i = 0; i < padd; i++)
                binary.append("0");
            }

              int i = (binary.length() - 8);
              int j = 0;
              char * pEnd;
              string rbinary;

            do{
                cout << char(strtol((string(binary.rbegin() + i, binary.rend() - j)).c_str(), &pEnd, 2));
                i -= 8;
                j += 8;
            }while(i >= 0 && (j <= binary.length() - 8));
        }
        else ;
    }

    return 0;
}
