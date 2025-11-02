// Medical system 
# include<bits/stdc++.h>
using namespace std;

class Medicine {
    public:
    int medid;
    string medname;
    string medmanufacturer;
    int medunits;
    
    Medicine(int id, string name, string manufacturer) {
        medid-id;
        medname=name;
        medmanufacturer=manufacturer;
    }
    
    void setmedunits(int units) {
        medunits=units;
    }
    
    bool getmedavalaibility(int requiredmedicinecount) {
        if(medunits>requiredmedicinecount) return true;
        return false;
    }
    
    void updatemedunits(int units) {
        medunits+=units;
    }
};

class Patient {
    public:
    int patid;
    string patname;
    string sufferingfrom = "";
    bool isadmitted = false;
    
    Patient(int id, string name) {
        patid=id;
        patname=name;
    }
    
    bool getpatientadmitstatus() {
        return isadmitted;
    }
    
    void setpatientadmitstatus(bool admitstatus) {
        isadmitted=admitstatus;
    }
    
    string patientdisease() {
        return sufferingfrom;
    }
    
    void setpatientdisease(string diseasename) {
        sufferingfrom=diseasename;
    }
    
    void setpatientdiseasetonull() {
        sufferingfrom="";
    }
}; 

class Doctor {
    public:
    int docid;
    string docname;
    string docspeciality;
    bool isavalaible = false;
    Doctor(int id, string name, string speciality) {
        docid=id;
        docname=name;
        docspeciality=speciality;
    }
    
    bool getdocavalaibility() {
        return isavalaible;
    }
    
    void setdocavalaibility(bool avalaibilitystatus){
        isavalaible=avalaibilitystatus;
    }
    
    string getdocspeciality() {
        return docspeciality;
    }
    
    string checkpatient(Patient* pat) {
        string diseasename;
        cout<<"Doctor: "<<docname<<" detected disease: "<<endl;
        cin>>diseasename;
        pat->setpatientdisease(diseasename);
        return diseasename;
    }
};

class PaymentStrategy{
    public:
    virtual void paybill(int price) = 0;
};

class CreditCardPayment : public PaymentStrategy {
    public:
    void paybill(int price) {
        cout<<"Payment done via credit card"<<endl;
    }
};

class UPIPayment : public PaymentStrategy{
    public:
    void paybill(int price) {
        cout<<"Payment done via upi"<<endl;
    }
};

class Hospital {
    public:
    string hospitalname;
    int hosid;
    vector<Doctor*> doctors;
    vector<Patient*> patients;
    vector<Medicine*> medicines;
    map<string, int> diseasetoamt;
    int capforpatients;
    
    Hospital(int id, string name, int cap) {
        hospitalname=name;
        hosid=id;
        capforpatients=cap;
    }
    
    void adddoctor(Doctor* doc) {
        doctors.push_back(doc);
    }
    
    void adddiseaseanditscharge(string diseasename, int charges) {
        diseasetoamt[diseasename]=charges;
    }
    
    bool isdiseasediagnosed(string diseasename) {
        if(diseasetoamt.find(diseasename)!=diseasetoamt.end()) return true;
        return false;
    }
    
    void admitpatient(Patient* pat, Doctor* doc) {
        if(patients.size()>=capforpatients) {
            cout<<"We dont have space to admit the patient sorry!"<<endl;
            return ;
        }
        string detecteddisease = doc->checkpatient(pat);
        if(detecteddisease=="") {
            cout<<"Patient is fine!";
            return ;
        }
        if(!isdiseasediagnosed(detecteddisease)) {
            cout<<"Patient is suffering from: "<<detecteddisease<<" but we dont have its cure!"<<endl;
            return;
        }
        cout<<"Patient is suffering from: "<<detecteddisease<<endl;
        pat->setpatientadmitstatus(true);
        patients.push_back(pat);
        cout<<"Patient is admitted to the hospital"<<endl;
    }
    
    void addmedicine(Medicine* med) {
        medicines.push_back(med);
    }
    
    int calcbill(Patient* pat) {
        string disease = pat->sufferingfrom;
        if(disease=="")  return 0;
        return diseasetoamt[disease];
    }
    
    void dischargepatient(Patient* pat, PaymentStrategy* ps) {
        if(pat->getpatientadmitstatus()==false) {
            cout<<"This patient is not admitted!";
            return;
        }
        pat->setpatientadmitstatus(false);
        pat->setpatientdiseasetonull();
        int amt = calcbill(pat);
        ps->paybill(amt);
    }
};

int main() {
    Hospital* hospital = new Hospital(1, "AIIMS Delhi", 5);
    hospital->adddiseaseanditscharge("Flu", 500);
    hospital->adddiseaseanditscharge("Covid", 2000);
    hospital->adddiseaseanditscharge("Injury", 1500);
    Doctor* doc1 = new Doctor(101, "Dr. Sharma", "General Physician");
    Doctor* doc2 = new Doctor(102, "Dr. Mehta", "Surgeon");
    hospital->adddoctor(doc1);
    hospital->adddoctor(doc2);
    Patient* pat1 = new Patient(201, "Ravi Kumar");
    Patient* pat2 = new Patient(202, "Anjali Singh");
    Medicine* med1 = new Medicine(301, "Paracetamol", "Cipla");
    med1->setmedunits(100);
    hospital->addmedicine(med1);
    cout << "Doctor will now diagnose Ravi Kumar...\n";
    hospital->admitpatient(pat1, doc1);
    PaymentStrategy* payment = new UPIPayment();
    hospital->dischargepatient(pat1, payment);
    return 0;
}