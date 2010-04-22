/* 

multichoose.cpp  -- k multichoose n for generic vectors

author: Erik Garrison <erik.garrison@bc.edu>
last revised: 2010-04-16

Copyright (c) 2010 by Erik Garrison

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

 */

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>


using namespace std;

template <class T> vector< vector<T> > multichoose(vector<T> objects, int k);
vector<vector<int> > multichoose(int n, int k);

ostream& operator<<(ostream& stream, vector<int>  m) {
    stream << "( ";
    for (vector<int> ::const_iterator i = m.begin(); i != m.end(); ++i) {
        stream << *i << " ";
    }
    stream << ")";
    return stream;
}

template <class T>
vector< vector<T> > multichoose(vector<T> objects, int k) {
    vector< vector<T> > results;
    vector<vector<int> > choices = multichoose((int)objects.size(), (int)k);
    for (vector<vector<int> >::const_iterator h = choices.begin();
            h != choices.end(); ++h) {
        vector<T> combination;
        int index = 0;
        for (vector<int> ::const_iterator i = h->begin(); i != h->end(); ++i) {
            for (int j = 0; j < *i; ++j) {
                combination.push_back(objects.at(index));
            }
            ++index;
        }
        results.push_back(combination);
    }
    return results;
}

vector<vector<int> > multichoose(int n, int k) {
    vector<vector<int> > multichoices;
    if (!k) {
        vector<int>  x (n, 0);
        multichoices.push_back(x);
        return multichoices;
    }
    if (!n) {
        return multichoices;
    }
    if (n == 1) {
        vector<int> x (1, k);
        multichoices.push_back(x);
        return multichoices;
    }
    vector<vector<int> > multichoices_head = multichoose(n - 1, k);
    for (vector<vector<int> >::iterator h = multichoices_head.begin(); 
            h != multichoices_head.end(); ++h) {
        h->insert(h->begin(),0);
        multichoices.push_back(*h);
    }
    vector<vector<int> > multichoices_tail = multichoose(n, k - 1);
    for (vector<vector<int> >::iterator h = multichoices_tail.begin(); 
            h != multichoices_tail.end(); ++h) {
        h->front()++;
        multichoices.push_back(*h);
    }
    return multichoices;
}

int main(int argc, char** argv) { 
    if (argc < 3) {
        cerr << "usage: " << endl
             << argv[0] << " <k> <item1> <item2> ... <itemN>  ~ n multichoose k" << endl;
        return 1;
    }

    int k = atoi(argv[1]);
    vector<string*> items;
    for (int i = 2; i < argc; ++i) {
        string* s = new string(argv[i]);
        items.push_back(s);
    }

    vector< vector<string*> > results = multichoose(items, k);

    for (vector< vector<string*> >::reverse_iterator i = results.rbegin(); i != results.rend(); ++i) {
        for (vector<string*>::const_iterator j = i->begin(); j != i->end(); ++j) {
            cout << **j << " ";
        }
        cout << endl;
    }

    return 0; 
}
