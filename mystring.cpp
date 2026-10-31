#include<iostream>
#include <utility>
using namespace std;
class mystring 
{
	private:
		char * str;
	public:
		mystring()
		{
			str=new char[1];
			str[0]='\0';
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
		void display () const
		{
			cout<<str<<endl;
		}
		mystring(const mystring &obj)
		{
			int len = obj.length();

			str = new char[len + 1];

			for(int i = 0; i <= len; i++)
			{
				str[i] = obj.str[i];
			}
		}

		mystring& operator=(const mystring &obj)
		{
			if(this == &obj)
			{
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
			delete[] str ;
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
			int len = 0;

			while(str[len] != '\0')
			{
				len++;
			}

			return len;
		}
		bool empty() const
		{
			return str[0] == '\0';
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


	// 1. Default Constructor
	mystring s1;
	cout << "Default Constructor: "<< endl;
	s1.display();

	// 2. Parameterized Constructor
	mystring s2("Hello");
	cout << "Parameterized Constructor: "<< endl;
	s2.display();

	// 3. Copy Constructor
	mystring s3 = s2;
	cout << "Copy Constructor: "<< endl ;
	s3.display();

	// 4. Copy Assignment
	mystring s4;
	s4 = s2;
	cout << "Copy Assignment: "<< endl;
	s4.display();

	// 5. Length
	cout << "Length: " << s2.length() << endl;

	// 6. Empty
	cout << "Is Empty: " << s1.empty() << endl;

	// 7. Addition Operator
	mystring s5(" World");
	mystring s6 = s2 + s5;
	cout << "Addition: "<< endl;
	s6.display();

	// 8. Equality Operator
	cout << "Equal: " << (s2 == s3) << endl;

	// 9. Not Equal Operator
	cout << "Not Equal: " << (s2 != s5) << endl;

	// 10. Subscript Operator
	cout << "Character: " << s2[1] << endl;
	mystring s13("Embedded");

	cout << "\nFirst Character: " << s13[0] << endl;
	cout << "Third Character: " << s13[2] << endl;

	// Modify a character
	s13[0] = 'e';

	cout << "After Modification: ";
	s13.display();

	// 11. Append Operator
	s2 += s5;
	cout << "Append: "<< endl;
	s2.display();

	// 12. Comparison Operators
	mystring a("Apple");
	mystring b("Banana");

	cout << "Less Than: " << (a < b) << endl;
	cout << "Greater Than: " << (a > b) << endl;

	// 13. c_str()
	cout << "C String: " << s2.c_str() << endl;

	// 14. Find
	cout << "\nFind Existing Character: " << s2.find('W') << endl;
	cout << "Find First Character: " << s2.find('H') << endl;
	cout << "Find Missing Character: " << s2.find('Z') << endl;

	// 15. Substring
	mystring s7 = s2.substr(0, 5);
	cout << "Substring: "<<endl;
	s7.display();

	// 16. Move Constructor
	mystring s8 = std::move(s7);
	cout << "Move Constructor: "<<endl;
	s8.display();

	// 17. Move Assignment
	mystring s9;
	s9 = std::move(s8);
	cout << "Move Assignment: "<< endl;
	s9.display();

	return 0;
}

