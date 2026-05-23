#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include<cctype>

using namespace std;

struct patient {
    int patient_id;
    string patient_name;
    int room_number;
    int duration_of_stay;
    int bill;
};

const int MAX_PATIENTS = 100;
const int room_price = 100;

bool id_exist(const patient patients[], int count, int newid) {

    for (int i = 0; i < count; i++) {
        if (patients[i].patient_id == newid) {
            return true;
        }
    }
    return false;
}

void addPatient(patient patients[], int& count) {
    int new_id;
    if (count >= MAX_PATIENTS) {
        cout << "System full! Cannot add more patients.\n";
        return;
    }
    cout << "---------------------------->" << endl;
    cout << "Enter patient details:" << endl;
    cout << endl;
    cout << "ID: ";
    cin >> new_id;
    cout << endl;

    if (id_exist(patients, count, new_id)) {
        cout << "--> Patient ID already exists!" << endl;
        cout << "--> try again: " << endl;
        addPatient(patients, count);
        return;
    }
    patients[count].patient_id = new_id;
    cout << "Name: ";
    cin >> patients[count].patient_name;
    cout << endl;

    patients[count].room_number = -1;
    patients[count].duration_of_stay = 0;
    patients[count].bill = patients[count].duration_of_stay * room_price;

    count++;
    cout << "--> Patient added successfully!" << endl;
    cout << "---------------------------->" << endl;
    cout << endl;
}

void display(patient pat[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "---------------------------->" << endl;
        cout << "patient " << i + 1 << " ." << endl;
        cout << endl;
        cout << "patient id : " << pat[i].patient_id << endl;
        cout << "patient name : " << pat[i].patient_name << endl;
        cout << "room number : " << pat[i].room_number << endl;
        cout << "duratrion of stay in days : " << pat[i].duration_of_stay << endl;
        cout << "patient's bill: " << pat[i].bill << "$" << endl;
        cout << "---------------------------->" << endl;
        cout << endl;
    }
}

void search_patient_id_and_name(patient pat[], int size) {

    cout << "---------------------------->" << endl;
    cout << "seach patient by id and name" << endl;
    cout << endl;

    int loop = 1;

    while (loop) {

        int id;
        string name;

        cout << "Enter patient ID to search: ";
        cin >> id;

        cout << endl;

        cout << "Enter patient name to search: ";
        cin >> name;

        bool found = 1;
        for (int i = 0; i < size; i++) {

            if (pat[i].patient_id == id && pat[i].patient_name == name) {
                cout << endl;
                cout << "--> patient found!" << endl;
                cout << endl;
                cout << "room number : " << pat[i].room_number << endl;
                cout << "duration of stay in days : " << pat[i].duration_of_stay << endl;
                cout << "patient's bill : " << pat[i].bill << "$" << endl;
                cout << endl;
                found = false;
                loop = 0;
            }
        }

        if (found) {
            loop = 1;
            cout << "--> the patient of this id " << id << " and name " << name << " is not found " << endl;
            cout << "--> try again." << endl;
            cout << endl;
        }

    }

    cout << "---------------------------->" << endl;
    cout << endl;
}

void update_patient(patient patients[], int count) {
    int id;
    bool patientFound = false;
    int patientIndex = -1;
    int updated_id = 0;

    while (!patientFound) {
        cout << endl;
        cout << "Enter patient ID to update: ";
        cin >> id;

        for (int i = 0; i < count; i++) {

            if (patients[i].patient_id == id) {
                patientFound = true;
                patientIndex = i;
                break;
            }
        }

        if (!patientFound && updated_id == 0) {
            cout << endl;
            cout << "--> Error: Patient with ID " << id << " not found! Please try again." << endl;
            cout << endl;
            cout << "--> enter another ID to search." << endl;
            cout << endl;
        }
    }


    patient& p = patients[patientIndex];
    cout << endl;
    cout << "--> patient found!" << endl;
    cout << endl;

    cout << "Current Name: " << p.patient_name << endl;
    cout << "Update Name: ";
    cin >> p.patient_name;


    cout << endl;

    while (true) {
        cout << endl;
        cout << "Current id: " << p.patient_id << endl;
        cout << "update id: ";
        cin >> updated_id;

        bool id_available = true;
        for (int i = 0; i < count; i++) {

            if (patients[i].patient_id == updated_id) {

                id_available = false;
                cout << endl;
                cout << "--> ID " << updated_id << " is already assigned to patient " << patients[i].patient_name;

                break;
            }
        }

        if (id_available) {

            p.patient_id = updated_id;

            break;
        }
        cout << endl;

    }

    cout << endl;

    int updated_room;
    bool duration = 1;
    while (true) {



        cout << p.patient_name << "'s " << "Current Room: " << p.room_number << endl;
        cout << "Assign a new Room (enter -1 if there is no room assigned to patient): ";
        cin >> updated_room;

        if (updated_room == -1) {

            p.room_number = -1;
            duration = 0;
            cout << "patient's id: " << p.patient_id << " not assigned to any room." << endl;
            break;
        }

        bool room_available = true;
        for (int i = 0; i < count; i++) {

            if (patients[i].room_number == updated_room && patients[i].patient_id != p.patient_id) {

                room_available = false;

                cout << "Room " << updated_room << " is already occupied by patient "
                    << patients[i].patient_name << " (ID: " << patients[i].patient_id << ")" << endl;
                break;
            }
        }

        if (room_available) {

            p.room_number = updated_room;
            cout << "Room " << updated_room << " successfully assigned to " << p.patient_name << endl;
            break;
        }
        cout << endl;
        cout << "--> enter another room to update." << endl;
        cout << endl;
    }

    cout << endl;
    if (duration) {
        cout << "Current duration of stay: " << p.duration_of_stay << " days" << endl;
        cout << "Update duration of stay: ";
        cin >> p.duration_of_stay;
    }
    else {
        cout << endl;
        cout << "--> patient is not assigned to a room, duration of stay = 0" << endl;
        p.duration_of_stay = 0;
    }


    cout << endl;

    p.bill = p.duration_of_stay * room_price;
    cout << "--> Patient's info successfully updated!" << endl;
    cout << endl;
}

bool check_room(const patient patients[], int count, int room) {
    if (room == -1) return false;
    for (int i = 0; i < count; i++) {
        if (patients[i].room_number == room) {
            return true;
        }
    }
    return false;
}

void set_room(patient& c, patient pat[], int size) {
    int new_room;
    while (true) {
        cout << "Enter room number to assign (enter -1 if there is no room assigned to patient): ";
        cin >> new_room;

        if (new_room == -1) {
            cout << "patient with id " << c.patient_id << " not assigned to a room." << endl;
            cout << endl;
            cout << "--> patient is not assigned to a room, duration of stay = 0" << endl;
            c.duration_of_stay = 0;
            return;
        }

        if (check_room(pat, size, new_room)) {
            cout << endl;
            cout << "--> Room " << new_room << " is already occupied. Please choose another room." << endl;
            cout << "--> try again." << endl;
            cout << endl;
        }
        else {
            c.room_number = new_room;
            cout << endl;
            cout << "Enter duration of stay (days): ";
            cin >> c.duration_of_stay;

            cout << endl;

            cout << "--> Room " << new_room << " successfully assigned to " << c.patient_name << ", patient will stay " << c.duration_of_stay << " days." << endl;
            c.bill = c.duration_of_stay * room_price;
            break;
        }

    }
}

void discharge_Patient(patient pat[], int& size) {
    int id;
    cout << "---------------------------->" << endl;
    cout << "Discharge and remove patient." << endl;
    cout << endl;

    while (true) {
        cout << "Enter patient ID to discharge: ";
        cin >> id;
        cout << endl;

        bool patientFound = false;

        for (int i = 0; i < size; i++) {
            if (pat[i].patient_id == id) {

                patientFound = true;
                cout << "--> patient found! " << endl;
                cout << endl;
                cout << "--> Patient " << pat[i].patient_name << " (ID: " << id << ") is discharged and removed from the system." << endl;
                cout << endl;

                for (int j = i; j < size - 1; j++) {
                    pat[j] = pat[j + 1];
                }

                size--;
                cout << "---------------------------->" << endl;
                cout << endl;
                return;
            }
        }

        if (!patientFound) {
            cout << "--> Error: Patient with ID " << id << " not found!" << endl;
            cout << "--> try again." << endl << endl;
        }
    }
}
void saveData(patient pat[], int count) {
    ofstream file("patients_data.txt");
    if (!file.is_open()) {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        file << pat[i].patient_id << " "
            << pat[i].patient_name << " "
            << pat[i].room_number << " "
            << pat[i].duration_of_stay << " "
            << pat[i].bill << "\n";
    }

    file.close();
    cout << "Patient data saved successfully!" << endl;
}

void loadData(patient pat[], int& size) {
    ifstream file("patients_data.txt");
    if (!file.is_open()) {
        cout << "No existing data found." << endl;
        return;
    }

    size = 0;
    while (file >> pat[size].patient_id) {
        file >> pat[size].patient_name;
        file >> pat[size].room_number;
        file >> pat[size].duration_of_stay;
        file >> pat[size].bill;
        size++;
    }

    file.close();
    cout << "Loaded " << size << " patient records." << endl;
}

void clearData(patient pat[], int& size) {
    size = 0;
    cout << "All patient data has been cleared." << endl;
}

int main() {
    patient pat[MAX_PATIENTS];
    int size = 0;
    int choice, id;
    string name;
    bool patientFound;

    loadData(pat, size);
    cout << endl;
    do {
        cout << "---------------------------------->" << endl;
        cout << "Hospital Management System" << endl;
        cout << "1. Add patient" << endl;
        cout << "2. Display all patients" << endl;
        cout << "3. Search patient by ID and Name" << endl;
        cout << "4. Update patient information" << endl;
        cout << "5. Assign room to patient" << endl;
        cout << "6. Discharge patient" << endl;
        cout << "7. Save data to file" << endl;
        cout << "8. Exit" << endl;
        cout << "9. clear all patient's data" << endl;
        cout << "---------------------------------->" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            addPatient(pat, size);
            break;
        case 2:
            display(pat, size);
            break;
        case 3:

            search_patient_id_and_name(pat, size);
            break;
        case 4:
            cout << "---------------------------->" << endl;;
            cout << "Update patient information." << endl;

            update_patient(pat, size);
            break;

        case 5:
            cout << "---------------------------->" << endl;
            cout << "Assign room to patient." << endl;
            cout << endl;
            cout << "Enter patient ID: ";
            cin >> id;
            cout << endl;

            patientFound = false;
            for (int i = 0; i < size; i++) {

                if (pat[i].patient_id == id) {

                    patientFound = true;

                    if (pat[i].room_number != -1) {

                        cout << "Patient already has room " << pat[i].room_number << " assigned." << endl;
                        cout << endl;
                        cout << "--> if you want to update it choose choice number 4 to update patient's info. " << endl;
                        cout << endl;
                        break;
                    }
                    set_room(pat[i], pat, size);
                    break;
                }
            }

            if (!patientFound) {

                cout << "Error: Patient with ID " << id << " not found!" << endl;
            }
            cout << "---------------------------->" << endl;
            cout << endl;
            break;

        case 6:

            discharge_Patient(pat, size);
            break;

        case 7:
            saveData(pat, size);
            break;

        case 8:
            cout << "Exiting the system." << endl;
            break;

        case 9:
            clearData(pat, size);
            break;

        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 8);

    return 0;
}