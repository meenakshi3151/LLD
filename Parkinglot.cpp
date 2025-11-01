#include<bits/stdc++.h>
using namespace std;


class Vehicle {
    public:
    int vehicleuniid;
    bool isparked = false;
    Vehicle(int vehicleid) {
        vehicleuniid=vehicleid;
    }
    bool getVehicleParked() {
        return isparked;
    }
    int getvehicleid() {
        return vehicleuniid;
    }
    void setvehicleparked(bool val) {
        isparked=val;
    }
    virtual string vehicletype() = 0;
};

class Car : public Vehicle {
    public:
    Car(int carid) : Vehicle(carid) {}
    string vehicletype() {
        return "CAR";
    }
};

class Truck : public Vehicle {
    public:
    Truck(int truckid) : Vehicle(truckid) {}

    string vehicletype() {
        return "TRUCK";
    }
};

class PaymentStrategy {
    public:
   virtual void paybill(int amt) = 0;
};

class UPIPayment : public PaymentStrategy {
    public:
    void paybill(int amt) {
        cout<<"Paid via UPI: "<<amt<<endl;
    } 
};

class CreditCardPayment : public PaymentStrategy {
    public:
    void paybill(int amt) {
        cout<<"Paid via Credit card: "<<amt<<endl;
    }
};

class Slot {
    public:
    static int totalslotsavailable;
    set<int> st;
    Slot(int slotscount) {
        totalslotsavailable=slotscount;
    }
    bool slotavalaibility() {
        if(totalslotsavailable>0) return true;
        return false;
    }
    int slotprice(string typeofvehicle) {
        if(typeofvehicle=="CAR") return 30;
        else if(typeofvehicle=="TRUCK") return 50;
        else {
            cout<<"We support only car and truck parkings!"<<endl;
            return -1;
        }
    }
    void bookslot(Vehicle* v) {
        if(slotavalaibility()) {
            totalslotsavailable--;
            st.insert(v->getvehicleid());
            v->setvehicleparked(true);
            cout<<"Slot is booked"<<endl;
            return;
        }
        cout<<"No avalaibility! Sorry next time"<<endl;
    }
    void exitslot(Vehicle* v, PaymentStrategy*  payment) {
        if(st.find(v->getvehicleid())!=st.end()) {
            st.erase(v->getvehicleid());
            int price = slotprice(v->vehicletype());
            payment->paybill(price);
            v->setvehicleparked(false);
            totalslotsavailable++;
            cout<<"You can go!! Thank you for choosing us!!"<<endl;
            return ;
        }
        cout<<"We cant find your booking with us!!"<<endl;
    }
};
int Slot::totalslotsavailable = 0;

int main() {
    Slot* slot = new Slot(5);
    Car* c1 = new Car(101);
    Truck* t1 = new Truck(202);
    UPIPayment* upi = new UPIPayment();
    CreditCardPayment* card = new CreditCardPayment();
    slot->bookslot(c1);
    slot->bookslot(t1);
    slot->exitslot(c1, upi);
    slot->exitslot(t1, card);
    return 0;
}