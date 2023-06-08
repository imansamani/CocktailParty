#include <iostream>
#include <string>
#include <uuid/uuid.h>
#include <unordered_map>
#include <random>
#include <thread>

std::string GenerateUID() {
    uuid_t uuid;
    uuid_generate_random(uuid);

    char uuidStr[37];
    uuid_unparse(uuid, uuidStr);

    return std::string(uuidStr);
}

class Person {
private:
    std::string uid;
    std::string interest;
    std::string location;

public:
    Person(std::string personInterest): interest(personInterest), location(""){
        uid = GenerateUID();
    }

    std::string UID() {
        return uid;
    }

    std::string Interest() {
        return interest;
    }

    std::string Location() {
        return location;
    }

    bool UpdateLocation(std::string personLocation) {
        location = personLocation;
        return true;
    }
};


class Room {
private:
    std::string name;
    std::unordered_map<std::string, Person*> persons;
    std::unordered_map<std::string, int> interests;

public:
    Room(std::string roomName): name(roomName) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Room& room) {
        os << "State in room " << room.name << " --->" <<std::endl;
        for (const auto& pair : room.interests) {
            os << pair.first << ": " << pair.second << "\n";
        }
        os << "<---";
        return os;
    }
    
    const std::string& Name() const {
        return name;
    }
    
    bool Empty() {
        return persons.empty();
    }
    
    const std::unordered_map<std::string, Person*>& Persons() const {
            return persons;
        }
    
    Person* PersonIn(std::string uid) {
        if (persons.count(uid) > 0) {
            return persons[uid];
        }
        return nullptr;
    }
    
    bool ShareInterests() {
        return interests.size() < persons.size();
    }
    
    bool addPerson(Person* person) {
        std::string uid = person->UID();
        if (PersonIn(uid)){
            return false;
        } else {
            persons[uid] = person;
            std::string interest = person->Interest();
            if (interests.count(interest) > 0) {
                ++interests[interest];
            } else {
                interests[interest] = 1;
            }
            person->UpdateLocation(name);
            return true;
        }
    }
    
    bool delPerson(Person* person) {
        std::string uid = person->UID();
        if (PersonIn(uid)) {
            --interests[person->Interest()];
            if (interests[person->Interest()] == 0) {
                interests.erase(person->Interest());
            }
            persons.erase(uid);
            person->UpdateLocation("");
            return true;
        } else {
            return false;
        }
    }
};


void Initialize(Room& room,
                int N,
                std::vector<std::string> interests =
                {"epidemiology", "biostatistics", "clinical research", "health policy"}) {
    std::cout << "Room A Initializing..." << std::endl;
    for (int i = 0; i < N; ++i) {
        int randIndex = std::rand() % interests.size();
        room.addPerson(new Person(interests[randIndex]));
    }
    std::cout << "Room " + room.Name() + " initialized with " << N << " persons." << std::endl;
    return;
}


void Simulate(Room& roomA, Room& roomB, int T) {
    std::cout << "Simulation Starts:" << std::endl;

    std::cout << roomA << std::endl;
    std::cout << roomB << std::endl;

    int n = 1;
    while (roomA.ShareInterests() && n <= T) {
        std::cout << "--- Time Step " << n << " ---" << std::endl;
        std::unordered_map<std::string, Person*> persons = roomA.Persons();
        auto it = persons.begin();
        std::advance(it, std::rand() % persons.size());
        Person* p1 = it->second;
        persons.erase(it->first);
        it = persons.begin();
        std::advance(it, std::rand() % persons.size());
        Person* p2 = it->second;
        // persons.erase(it);
        std::cout << p1->Interest() << " <--> " << p2->Interest() << std::endl;
        if (p1->Interest() == p2->Interest()) {
            roomA.delPerson(p1);
            roomA.delPerson(p2);
            roomB.addPerson(p1);
            roomB.addPerson(p2);
            std::cout << "Persons grouped and moved to room B :)" << std::endl;
        } else {
            std::cout << "Persons rejoin the pool of available people in room A :(" << std::endl;
        }
        std::cout << roomA << std::endl;
        std::cout << roomB << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        n++;
    }
    std::cout << "--- --------- ---" << std::endl;

    if (!roomA.ShareInterests()) {
        std::cout << "There are no more possible groupings." << std::endl;
        std::cout << "Final Status:" << std::endl;
        std::cout << roomA << std::endl;
        std::cout << roomB << std::endl;
    } else if (roomA.ShareInterests() && n > T) {
        std::cout << "Max number of iterations reached." << std::endl;
        std::cout << "Final Status:" << std::endl;
        std::cout << roomA << std::endl;
        std::cout << roomB << std::endl;
    }
    std::cout << "Simulation Finished." << std::endl;
    return;
}

void PersonInfo(std::string uid, Room& roomA, Room& roomB){
    
    if (roomA.PersonIn(uid)){
        std::cout << "The person is in room "
        << roomA.Name()
        << " and is interested in "
        << roomA.PersonIn(uid)->Interest()
        << "."<<std::endl;
    }
    else if (roomB.PersonIn(uid)){
        std::cout << "The person is in room "
        << roomB.Name()
        << " and is interested in "
        << roomB.PersonIn(uid)->Interest()
        << "."<<std::endl;
    }
    else {
        std::cout<<"The person is not present in either of the rooms."<<std::endl;
    }
    return;
}

int main() {
    
    int N {100};
    Room roomA("A");
    Room roomB("B");
    Initialize(roomA, N);
    Simulate(roomA, roomB, 300);
    
    std::cout<<"-------->"<<std::endl;
    std::cout<<"Iman declared as a Person interested in Software Engineering..."<<std::endl;
    Person Iman("Software Engineering");
    std::cout<<"Checking his info:"<<std::endl;
    PersonInfo(Iman.UID(), roomA, roomB);
    std::cout<<"Moving him to room A..."<<std::endl;
    roomA.addPerson(&Iman);
    std::cout<<"Checking his info:"<<std::endl;
    PersonInfo(Iman.UID(), roomA, roomB);
    std::cout<<"Leaving room A and moving to room B..."<<std::endl;
    roomA.delPerson(&Iman);
    roomB.addPerson(&Iman);
    std::cout<<"Checking his info:"<<std::endl;
    PersonInfo(Iman.UID(), roomA, roomB);
    std::cout<<"Leaving room B..."<<std::endl;
    roomB.delPerson(&Iman);
    std::cout<<"<--------"<<std::endl;
    
    return 0;
}
