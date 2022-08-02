//reza ebadi ozan 
//4002023025

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct infoOfLessons {
	char name1[30];
	char name2[30];
	int number;
	int vahed;
	int zarfiat;
};
struct information {
	string studentCode;
	char firstname[40];
	char lastname[40];
	int shahrie;
	int tedadDars;
	int index[50];
	information * next;
};
information *add(information *head, information *new_student) {
	information *first = head;
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = new_student;
	new_student->next = NULL;
	return first;
}

void print_list(information *head) {
	while (head) {
		cout << head->studentCode << " ";
		head = head->next;
	}
	cout << endl;
}
void printLesson(int index[], infoOfLessons * b, int tedad) {

	for (int i = 0; i<tedad; i++) {
		infoOfLessons cpy1;
		int l = index[i];
		//cpy1=b[l];
		cout << i << "." << b[l].name1 << " " << b[l].name2 << "\n";
	}
}
void addLesson(int index[], int addIndex, int& tedad_dars) {
	for (int i = 0; i<tedad_dars; i++) {
		if (index[i] == addIndex) {
			cout << " you can't choose this lesson again";
			return;
		}
		
	}
	index[tedad_dars] = addIndex;
	++tedad_dars;
}

int*  deleteLesson(int index[], int deleteIndex, int &tedad_dars) {
	int * ans = new int[50];
	int k = 0;
	int count_lesson = 0;
	for (int i = 0; i<tedad_dars; i++) {
		if (index[i] != deleteIndex) {
			ans[k] = index[i]; ++k;
			++count_lesson;
		}
	}
	if (count_lesson != tedad_dars) {
		--tedad_dars;
	}
	return ans;
}
int main() {
	int j = 0;

	infoOfLessons * temp = new infoOfLessons[100];
	fstream darsFile("lessons.txt", ios::in);
	while (!darsFile.eof()) {
		darsFile >> temp[j].name1 >> temp[j].name2 >> temp[j].number >> temp[j].vahed >> temp[j].zarfiat;
		++j;
	}

	information * head = new information;

	fstream student("students.txt", ios::in);
	student >> head->studentCode >> head->firstname >> head->lastname >> head->shahrie >> head->tedadDars;
	int m = 0;
	int find;
	char a[30], b[30], c[30];
	for (int i = 0; i<head->tedadDars; ++i) {
		student >> a >> b >> find >> c;
		for (int l = 0; l<j + 1; ++l)
			if (find == temp[l].number) {
				head->index[m] = l;
				m++;
			}
	}
	information * temp2 = new information;
	int student_count=1;
	int n = 0;
	int find1 = 0;
	char a1[10], b1[10], c1[10];
	while (!student.eof()) {
		student >> temp2->studentCode;
		student >> temp2->firstname;
		student >> temp2->lastname;
		student >> temp2->shahrie;
		student >> temp2->tedadDars;

		for (int i = 0; i<temp2->tedadDars; i++) {
			student >> a1 >> b1 >> find1 >> c1;
			for (int p = 0; p<j + 1; p++) {
				if (find1 == temp[p].number) {
					temp2->index[n] = p;
					++n;
				}
			}
			head->next = NULL;
			add(head, temp2);
		}
		++student_count;
	}
	darsFile.close();
	student.close();

	cout << "**********************************************\n";
	cout << "welcome\n";
	cout << "please enter yout student code:\n";
	string number_student;
	cin >> number_student;
	cout << "\n";
	information * cpy = head;
	while (1) {
		if (number_student == cpy->studentCode) {
			cout << "DONE\n\n";
			break;
		}
		cpy = cpy->next;
		if (cpy == NULL) {
			cout << "EROR 404\nyour student code not found\n";
			return 0;

		}
	}
	cout << "welcome"<<" "<<cpy->firstname<<endl;
	while (1) {
		cout << "please enter your choice:\n";
		cout << "1.print lessons\n";
		cout << "2.add lesson\n";
		cout << "3.delete lesson\n";
		cout << "4.exit\n";
		int choice;
		cin >> choice;
		if (choice == 1) {
			printLesson(cpy->index, temp, cpy->tedadDars);
		}
		int entered_index;
		if (choice == 2) {
			for (int p = 0; p<j; p++) {
				cout << p << "." << temp[p].name1 << " " << temp[p].name2 << endl;
			}
			cout << "please enter the number of lesson:\n";
			cin >> entered_index;
			addLesson(cpy->index, entered_index, cpy->tedadDars);
		}
		if (choice == 3) {
			printLesson(cpy->index, temp, cpy->tedadDars);
			cout << "please enter index of lesson thay you want delete it:\n";
			int delete_index;
			cin >> delete_index;
			cout << "\n";
			int m = 0;
			int * a = new int[50];
			a = deleteLesson(cpy->index, delete_index, cpy->tedadDars);
			for (int c = 0; c<cpy->tedadDars; ++c) {
				cpy->index[m] = a[c];
				++m;
			}
		}
		if (choice == 4) { break; }
		cout << "**********************************************\n";
	}
     fstream student2("students.txt", ios::out);
    information * write=head;
    for(int k=0;k<student_count;++k){
    	student2<<write->studentCode<<"\n"<<write->firstname<<" "<<write->lastname<<"\n"<<write->shahrie<<"\n"<<write->tedadDars<<"\n";
    	 for(int s=0;s<write->tedadDars;s++){
    	 	
    	 	student2<<temp[write->index[s]].name1<<" "<<temp[write->index[s]].name2<<" "<<temp[write->index[s]].number<<" "<<temp[write->index[s]].vahed<<"\n";
		 }
		 write=write->next;
	}
  student2.close();
delete []temp;
delete temp2;
delete a;
	return 0;
}
