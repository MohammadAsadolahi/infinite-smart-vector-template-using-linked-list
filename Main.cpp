/*
 * SmartVector.cpp
 *
 *      Author: mohammad asadolahi
 *        https://github.com/mohammadAsadolahi
 */

#include "SmartVector.cpp"

auto main (int argc ,char *argv[])-> int
	{
		cout << argv[0] << endl;
		try
			{
				SmartVector<int >numbers;
				numbers.add(23);
				numbers.add(24);
				numbers.add(25);
				numbers.add(26);
				cout << "total object's :" << numbers.getCount( );
				cout << endl << numbers[1] << endl;
				numbers[0] = 28;
				numbers.remove(1);
				numbers[9] = 28;
				numbers.remove(9);
				cout << "total object's :" << numbers.getCount( );
			}
		catch (unique_ptr<Exception >&exception)
			{
				(*exception) << cout;
			}
		catch (...)
			{
				cout << endl << "we are sorry something went wrong!";
			}
		cout << endl << "program ended.";
	}
