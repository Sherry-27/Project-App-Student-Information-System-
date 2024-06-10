#include <iostream>
#include <cstdlib> 
using namespace std;

struct students {
    int SID;
    students* snext;
};

struct courses {
    int CID;
    courses* cnext;
    students* fstud;
};

void cinsert(courses** cstart) {
    courses* cptr = new courses;
    cout << "Insert Course Number: ";
    cin >> cptr->CID;
    cptr->cnext = nullptr;
    cptr->fstud = nullptr;
    if (*cstart == nullptr) {
        *cstart = cptr;
    } else {
        courses* curr = *cstart;
        while (curr->cnext != nullptr) {
            curr = curr->cnext;
        }
        curr->cnext = cptr;
    }
}

void cprint(courses** cstart) {
    courses* curr = *cstart;
    while (curr != nullptr) {
        cout << "Course Number: " << curr->CID << endl;
        cout << "" << endl;
        curr = curr->cnext;
    }
}

void csearch(courses** cstart) {
    int toSearch;
    cout << "Enter course number: ";
    cin >> toSearch;

    courses* curr = *cstart;
    while (curr != nullptr) {
        if (curr->CID == toSearch) {
            cout << "Course Exists " << endl;
            return;
        }
        curr = curr->cnext;
    }
    cout << "Course doesn't exist" << endl;
}

void cdel(courses** cstart) {
    int toDelete;
    cout << "Insert course number: ";
    cin >> toDelete;
    
    courses* curr = *cstart;
    courses* prev = nullptr;

    while (curr != nullptr && curr->CID != toDelete) {
        prev = curr;
        curr = curr->cnext;
    }

    if (curr == nullptr) {
        cout << "Course doesn't exist" << endl;
        return;
    }

    if (prev == nullptr) {
        *cstart = curr->cnext;
    } else {
        prev->cnext = curr->cnext;
    }

    // Delete enrolled students
    students* studCurr = curr->fstud;
    while (studCurr != nullptr) {
        students* nextStud = studCurr->snext;
        delete studCurr;
        studCurr = nextStud;
    }

    delete curr;
}

void studinsert(students** studstart, courses** cstart) {
    students* sptr = new students;
    cout << "Insert Student ID: ";
    cin >> sptr->SID;
    sptr->snext = nullptr;

    int CID;
    cout << "Insert course number in which you want to enroll the student: ";
    cin >> CID;

    courses* curr = *cstart;
    while (curr != nullptr) {
        if (CID == curr->CID) {
            if (curr->fstud == nullptr) {
                curr->fstud = sptr;
            } else {
                students* stcurr = curr->fstud;
                while (stcurr->snext != nullptr) {
                    stcurr = stcurr->snext;
                }
                stcurr->snext = sptr;
            }
            cout << "Enrolled successfully" << endl;
            return;
        }
        curr = curr->cnext;
    }
    cout << "Course doesn't exist" << endl;
    delete sptr; // Delete the student as it's not enrolled
}

void pstudwrtcour(courses** cstart) {
    int searchCourse;
    cout << "Enter course number: ";
    cin >> searchCourse;

    courses* curr = *cstart;
    while (curr != nullptr) {
        if (searchCourse == curr->CID) {
            cout << "Course " << curr->CID << " exists" << endl;
            cout << "Enrolled students: " << endl;
            students* studlist = curr->fstud;

            while (studlist != nullptr) {
                cout << "Student ID: " << studlist->SID << endl;
                studlist = studlist->snext;
            }
            return;
        }
        curr = curr->cnext;
    }
    cout << "Course doesn't exist" << endl;
}

int main() {
    courses* cstart = nullptr;
    students* studstart = nullptr;

    int select = 1;
    while (select != 0) {
        cout << "Press 1 to insert a course" << endl;
        cout << "Press 2 to delete a course" << endl;
        cout << "Press 3 to print courses" << endl;
        cout << "Press 4 to search a course" << endl;
        cout << "Press 5 to insert a student" << endl;
        cout << "Press 6 to print students" << endl;
        cout << "Press 7 to print course and enrolled students" << endl;
        cout << "Press 0 to exit" << endl;
        cout << "Enter your choice: ";
        cin >> select;

        switch (select) {
            case 1:
                cinsert(&cstart);
                break;
            case 2:
                cdel(&cstart);
                break;
            case 3:
                cprint(&cstart);
                break;
            case 4:
                csearch(&cstart);
                break;
            case 5:
                studinsert(&studstart, &cstart);
                break;
            case 6:
                break;
            case 7:
                pstudwrtcour(&cstart);
                break;
            case 0:
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }
    }

    return 0;
}

