#include<iostream>
#include <utility>
#include <fstream>


using namespace std;
class mystring 
{
	private:
		char * str;
	public:
		mystring()
		{
	    str=0;
		}

		mystring(const char *s)
		{
			if(s == nullptr)
			{
				str = new char[1];
				str[0] = '\0';
				return;
			}
			int len=0;
			while(s[len]!='\0')
			{
				len++;
			}
			str = new char[len+1];
			for(int i=0;i<=len;i++)
			{
				str[i]=s[i];
			}
		}
		

            void display() const
{
    if(str != nullptr)
        cout << str << endl;
    else
        cout << endl;
}

mystring(const mystring &obj)
{
    if(obj.str == nullptr)
    {
        str = nullptr;
        return;
    }

    int len = obj.length();

    str = new char[len + 1];

    for(int i = 0; i <= len; i++)
    {
        str[i] = obj.str[i];
    }
}



                  
                // Stream Extraction Operator Overloading
friend istream& operator>>(istream &in, mystring &obj)
{
    ofstream fout("temp.txt");

    char ch;

    in >> ws;

    // Read input character by character
    while(in.get(ch) && ch != '\n')
    {
        fout.put(ch);
    }

    fout.close();

    // Open the file for reading
    ifstream fin("temp.txt");

    // Move file pointer to the end
    fin.seekg(0, ios::end);

    // Calculate file size
    int size = fin.tellg();

    // Allocate memory based on file size
    char *temp = new char[size + 1];

    // Move file pointer to beginning
    fin.seekg(0, ios::beg);

    // Read file contents
    fin.read(temp, size);

    // Add null character
    temp[size] = '\0';

    fin.close();

    // Replace old string
    delete[] obj.str;

    obj.str = temp;

    return in;
}


 // Insertion Operator Overloading
friend ostream& operator<<(ostream &out, const mystring &obj)
{
    if(obj.str != nullptr)
        out << obj.str;

    return out;
}

  mystring& operator=(const mystring &obj)
{
    // Check self assignment
    if(this == &obj)
    {
        return *this;
    }

    // Check whether source pointer is NULL
    if(obj.str == nullptr)
    {
        delete[] str;
        str = nullptr;

        return *this;
    }

    int len = obj.length();

    char *temp = new char[len + 1];

    for(int i = 0; i <= len; i++)
    {
        temp[i] = obj.str[i];
    }

    delete[] str;

    str = temp;

    return *this;
}
		~mystring()
		{
			if(str!=nullptr){
			delete[] str ;
			str=nullptr;
			}
			cout <<" Destructor called !!!!" << endl;
		}
		mystring(mystring &&obj)
		{
			char *empty = new char[1];
			empty[0] = '\0';

			str = obj.str;
			obj.str = empty;
		}
		mystring& operator=(mystring &&obj)
		{
			if(this == &obj)
			{
				return *this;
			}

			char *empty = new char[1];
			empty[0] = '\0';

			delete[] str;

			str = obj.str;
			obj.str = empty;

			return *this;
		}
		
               int length() const
{
    if(str == nullptr)
        return 0;

    int len = 0;

    while(str[len] != '\0')
    {
        len++;
    }

    return len;
}


bool empty() const
{
    return str == nullptr || str[0] == '\0';
}



		mystring operator+(const mystring &obj) const
		{
			int len1 = length();
			int len2 = obj.length();

			mystring temp;

			delete[] temp.str;

			temp.str = new char[len1 + len2 + 1];

			int i = 0;

			for(; i < len1; i++)
			{
				temp.str[i] = str[i];
			}

			for(int j = 0; j < len2; j++)
			{
				temp.str[i + j] = obj.str[j];
			}

			temp.str[i + len2] = '\0';

			return temp;
		}
		
bool operator==(const mystring &obj) const
{
    // Check whether both pointers are NULL
    if(str == nullptr && obj.str == nullptr)
    {
        return true;
    }

    // Check whether only one pointer is NULL
    if(str == nullptr || obj.str == nullptr)
    {
        return false;
    }

    int i = 0;

    while(str[i] != '\0' && obj.str[i] != '\0')
    {
        if(str[i] != obj.str[i])
        {
            return false;
        }

        i++;
    }

    return str[i] == obj.str[i];
}




		bool operator!=(const mystring &obj) const
		{
			return !(*this == obj);
		}

		char& operator[](int index)
		{
			return str[index];
		}

		const char& operator[](int index) const
		{
			return str[index];
		}

		mystring& operator+=(const mystring &obj)
		{
			int len1 = length();
			int len2 = obj.length();

			char *temp = new char[len1 + len2 + 1];

			int i = 0;

			for(; i < len1; i++)
			{
				temp[i] = str[i];
			}

			for(int j = 0; j < len2; j++)
			{
				temp[i + j] = obj.str[j];
			}

			temp[len1 + len2] = '\0';

			delete[] str;
			str = temp;

			return *this;
		}
		
              bool operator<(const mystring &obj) const
{
    // Both pointers are NULL
    if(str == nullptr && obj.str == nullptr)
    {
        return false;
    }

    // First pointer is NULL
    if(str == nullptr)
    {
        return true;
    }

    // Second pointer is NULL
    if(obj.str == nullptr)
    {
        return false;
    }

    int i = 0;

    while(str[i] != '\0' && obj.str[i] != '\0')
    {
        if(str[i] < obj.str[i])
            return true;

        if(str[i] > obj.str[i])
            return false;

        i++;
    }

    return str[i] < obj.str[i];
}

		bool operator>(const mystring &obj) const
		{
			return obj < *this;
		}
		const char* c_str() const
		{
			return str;
		}


	int find(char ch) const
{
    if(str == nullptr)
    {
        return -1;
    }

    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ch)
        {
            return i;
        }
    }

    return -1;
}

		mystring substr(int start, int count) const
		{
			int len = length();

			if(start < 0 || start >= len || count <= 0)
			{
				return mystring();
			}

			if(count > len - start)
			{
				count = len - start;
			}

			mystring temp;
			delete[] temp.str;

			temp.str = new char[count + 1];

			for(int i = 0; i < count; i++)
			{
				temp.str[i] = str[start + i];
			}

			temp.str[count] = '\0';

			return temp;
		}
};
int main()
{
    cout << "\n========================================" << endl;
    cout << "       CUSTOM STRING CLASS TESTING      " << endl;
    cout << "========================================" << endl;


    // ==========================================
    // 1. CONSTRUCTOR TESTING
    // ==========================================

    cout << "\n[1] CONSTRUCTOR TESTING" << endl;

    mystring s1;
    mystring s2("Hello");

    cout << "Default Constructor: ";
    s1.display();

    cout << "Parameterized Constructor: ";
    s2.display();


    // ==========================================
    // 2. COPY CONSTRUCTOR AND ASSIGNMENT
    // ==========================================

    cout << "\n[2] COPY OPERATIONS" << endl;

    mystring s3(s2);
    cout << "Copy Constructor: ";
    s3.display();

    mystring s4;
    s4 = s2;

    cout << "Copy Assignment: ";
    s4.display();


    // ==========================================
    // 3. MOVE CONSTRUCTOR AND ASSIGNMENT
    // ==========================================

    cout << "\n[3] MOVE OPERATIONS" << endl;

    mystring s5("Move Constructor");

    mystring s6(std::move(s5));

    cout << "Move Constructor Destination: ";
    s6.display();

    cout << "Moved From Object: ";
    s5.display();

    mystring s7("Move Assignment Source");
    mystring s8;

    s8 = std::move(s7);

    cout << "Move Assignment Destination: ";
    s8.display();

    cout << "Moved From Object: ";
    s7.display();


    // ==========================================
    // 4. STRING INFORMATION
    // ==========================================

    cout << "\n[4] STRING INFORMATION" << endl;

    cout << "Length: " << s2.length() << endl;
    cout << "Is Empty: " << s1.empty() << endl;


    // ==========================================
    // 5. STRING CONCATENATION
    // ==========================================

    cout << "\n[5] STRING CONCATENATION" << endl;

    mystring s9("Hello");
    mystring s10(" World");

    mystring s11 = s9 + s10;

    cout << "Addition: ";
    s11.display();

    s9 += s10;

    cout << "Append: ";
    s9.display();


    // ==========================================
    // 6. COMPARISON OPERATORS
    // ==========================================

    cout << "\n[6] COMPARISON OPERATORS" << endl;

    mystring s12("Hello");
    mystring s13("World");

    cout << "Equal: " << (s12 == s13) << endl;
    cout << "Not Equal: " << (s12 != s13) << endl;
    cout << "Less Than: " << (s12 < s13) << endl;
    cout << "Greater Than: " << (s12 > s13) << endl;


    // ==========================================
    // 7. SUBSCRIPT OPERATOR
    // ==========================================

    cout << "\n[7] SUBSCRIPT OPERATOR" << endl;

    mystring s14("Embedded");

    cout << "First Character: " << s14[0] << endl;
    cout << "Third Character: " << s14[2] << endl;


    // ==========================================
    // 8. STRING MODIFICATION
    // ==========================================

    cout << "\n[8] STRING MODIFICATION" << endl;

    mystring s15("Embedded");

    s15[0] = 'e';

    cout << "After Modification: ";
    s15.display();


    // ==========================================
    // 9. FIND OPERATION
    // ==========================================

    cout << "\n[9] FIND OPERATION" << endl;

    mystring s16("Embedded");

    cout << "Find 'b': " << s16.find('b') << endl;
    cout << "Find 'E': " << s16.find('E') << endl;
    cout << "Find 'z': " << s16.find('z') << endl;


    // ==========================================
    // 10. SUBSTRING OPERATION
    // ==========================================

    cout << "\n[10] SUBSTRING OPERATION" << endl;

    mystring s17("Embedded System");

    mystring s18 = s17.substr(0, 8);

    cout << "Original String: ";
    s17.display();

    cout << "Substring: ";
    s18.display();


    // ==========================================
    // 11. C STRING ACCESS
    // ==========================================

    cout << "\n[11] C STRING ACCESS" << endl;

    cout << "C String: " << s17.c_str() << endl;


    // ==========================================
    // 12. STREAM INSERTION AND EXTRACTION
    // ==========================================

    cout << "\n[12] STREAM OPERATORS" << endl;

    mystring s19("Embedded");

    cout << "Insertion Operator: " << s19 << endl;

    mystring s20;

    cout << "Enter a string: ";
    cin >> s20;

    cout << "Extraction Operator: " << s20 << endl;


    // ==========================================
    // 13. NULL STRING TESTING
    // ==========================================

    cout << "\n[13] NULL STRING TESTING" << endl;

    mystring n1;

    cout << "NULL Display: ";
    n1.display();

    cout << "NULL Length: " << n1.length() << endl;
    cout << "NULL Is Empty: " << n1.empty() << endl;

    cout << "NULL C String: ";

    if(n1.c_str() == nullptr)
        cout << "NULL pointer" << endl;
    else
        cout << n1.c_str() << endl;


    // ==========================================
    // 14. NULL COPY AND MOVE OPERATIONS
    // ==========================================

    cout << "\n[14] NULL COPY AND MOVE TESTING" << endl;

    mystring n2(n1);

    cout << "NULL Copy Constructor: ";
    n2.display();

    mystring n3("Hello");
    n3 = n1;

    cout << "NULL Copy Assignment: ";
    n3.display();

    mystring n4;

    mystring n5(std::move(n4));

    cout << "NULL Move Constructor: ";
    n5.display();

    mystring n6("Hello");
    mystring n7;

    n6 = std::move(n7);

    cout << "NULL Move Assignment: ";
    n6.display();


    // ==========================================
    // 15. SELF-ASSIGNMENT TESTING
    // ==========================================

    cout << "\n[15] SELF-ASSIGNMENT TESTING" << endl;

    mystring n8("Embedded");

    n8 = n8;

    cout << "Self Copy Assignment: ";
    n8.display();

    mystring n9("Embedded");

    n9 = std::move(n9);

    cout << "Self Move Assignment: ";
    n9.display();


    // ==========================================
    // 16. NULL STRING CONCATENATION
    // ==========================================

    cout << "\n[16] NULL CONCATENATION TESTING" << endl;

    mystring n10;
    mystring n11("Embedded");

    mystring n12 = n10 + n11;

    cout << "NULL + String: ";
    n12.display();

    n10 += n11;

    cout << "NULL += String: ";
    n10.display();

    mystring n13;
    mystring n14;

    mystring n15 = n13 + n14;

    cout << "NULL + NULL: ";
    n15.display();

    cout << "Result Is Empty: " << n15.empty() << endl;


    // ==========================================
    // 17. NULL COMPARISON TESTING
    // ==========================================

    cout << "\n[17] NULL COMPARISON TESTING" << endl;

    mystring n16;
    mystring n17;
    mystring n18("Hello");

    cout << "NULL == NULL: " << (n16 == n17) << endl;
    cout << "NULL == Hello: " << (n16 == n18) << endl;
    cout << "NULL != Hello: " << (n16 != n18) << endl;

    cout << "NULL < Hello: " << (n16 < n18) << endl;
    cout << "Hello < NULL: " << (n18 < n16) << endl;

    cout << "NULL > Hello: " << (n16 > n18) << endl;
    cout << "Hello > NULL: " << (n18 > n16) << endl;


    // ==========================================
    // 18. NULL FIND AND SUBSTRING TESTING
    // ==========================================

    cout << "\n[18] NULL FIND AND SUBSTRING TESTING" << endl;

    cout << "NULL Find: " << n16.find('H') << endl;

    mystring n19 = n16.substr(0, 3);

    cout << "NULL Substring: ";
    n19.display();


    // ==========================================
    // 19. NULL SUBSCRIPT CHECK
    // ==========================================

    cout << "\n[19] NULL SUBSCRIPT CHECK" << endl;

    if(n16.c_str() == nullptr)
        cout << "NULL string - Subscript access skipped" << endl;
    else
        cout << n16[0] << endl;


    // ==========================================
    // 20. NULL STREAM INSERTION
    // ==========================================

    cout << "\n[20] NULL STREAM INSERTION" << endl;

    cout << "NULL String: " << n16 << endl;


    // ==========================================
    // END OF TESTING
    // ==========================================

    cout << "\n========================================" << endl;
    cout << "       ALL TESTS EXECUTED              " << endl;
    cout << "========================================" << endl;

    return 0;
}

