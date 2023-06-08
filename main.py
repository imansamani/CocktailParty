import time
import uuid
import random


def generate_unique_id():
    return str(uuid.uuid4())


class Person:
    def __init__(self, interest):
        self.__uid = generate_unique_id()
        self.__interest = interest
        self.__location = None

    def uid(self):
        return self.__uid

    def interest(self):
        return self.__interest

    def location(self):
        return self.__location

    def updateLocation(self, location):
        self.__location = location
        return True


class Room:
    def __init__(self, name):
        self.__name = name
        self.__persons = {}
        self.__interests = {}

    def __str__(self):
        output = [key + " " + str(value) + "\n" for key, value in self.__interests.items()]
        return "State in room " + self.__name + " --->" + "\n" + "".join(output) + "<---"

    def name(self):
        return self.__name

    def persons(self):
        return self.__persons.values()

    def empty(self):
        if self.__persons:
            return False
        return True

    def personIn(self, uid):
        if uid in self.__persons:
            return self.__persons[uid]
        return False

    def shareInterests(self):
        if len(self.__interests) < len(self.__persons):
            return True
        return False

    def addPerson(self, person):
        if isinstance(person, Person):
            if person.uid() not in self.__persons:
                self.__persons[person.uid()] = person
                interest = person.interest()
                if interest in self.__interests:
                    self.__interests[interest] += 1
                else:
                    self.__interests[interest] = 1
                person.updateLocation(self.__name)
                return True
            else:
                return False
        else:
            return False

    def delPerson(self, person):
        if isinstance(person, Person):
            uid = person.uid()
            if self.personIn(uid):
                self.__interests[person.interest()] -= 1
                if self.__interests[person.interest()] == 0:
                    del self.__interests[person.interest()]
                del self.__persons[uid]
                person.updateLocation(None)
                return True
            else:
                return False
        else:
            return False


def initialize(N, interests):
    roomA = Room("A")
    roomB = Room("B")

    print("Room A Initializing...")
    for i in range(N):
        roomA.addPerson(Person(interests[random.randint(0, len(interests)-1)]))
    print("Room A initialized with " + str(N) + " persons.")
    return roomA, roomB


def simulate(roomA, roomB, T):
    print("Simulation Starts:")

    print(roomA)
    print(roomB)

    n = 1
    while roomA.shareInterests() and n <= T:
        print("--- Time Step " + str(n) + " ---")
        p1, p2 = random.sample([*roomA.persons()], k=2)
        print(p1.interest() + " <--> " + p2.interest())
        if p1.interest() == p2.interest():
            roomA.delPerson(p1)
            roomA.delPerson(p2)
            roomB.addPerson(p1)
            roomB.addPerson(p2)
            print("Persons grouped and moved to room B :)")
        else:
            print("Persons rejoin the pool of available people in room A :(")
        print(roomA)
        print(roomB)
        time.sleep(1)
        n += 1

    print("--- --------- ---")
    
    if not roomA.shareInterests():
        print("There are no more possible groupings.")
        print("Final Status:")
        print(roomA)
        print(roomB)
    elif roomA.shareInterests() and n > T:
        print("Max number of iterations reached.")
        print("Final Status:")
        print(roomA)
        print(roomB)
    print("Simulation Finished.")
    return roomA, roomB


def person_info(uid, roomA, roomB):
    if roomA.personIn(uid):
        print("The person is in room " + roomA.name() + " and is interested in " + roomA.personIn(uid).interest() + ".")
        return True
    elif roomB.personIn(uid):
        print("The person is in room " + roomB.name() + " and is interested in " + roomB.personIn(uid).interest() + ".")
        return True
    else:
        print("The person is not present in either of the rooms.")
        return False


if __name__ == "__main__":
    roomA, roomB = initialize(100, ["epidemiology", "biostatistics", "clinical research", "health policy"])
    roomA, roomB = simulate(roomA, roomB, 300)

    print("-------->")
    print("Iman declared as a Person interested in Software Engineering...")
    Iman = Person("Software Engineering")
    print("Checking his info:")
    person_info(Iman.uid(), roomA, roomB)
    print("Moving him to room A...")
    roomA.addPerson(Iman)
    print("Checking his info:")
    person_info(Iman.uid(), roomA, roomB)
    print("Leaving room A and moving to room B...")
    roomA.delPerson(Iman)
    roomB.addPerson(Iman)
    print("Checking his info:")
    person_info(Iman.uid(), roomA, roomB)
    print("Leaving room B...")
    roomB.delPerson(Iman)
    print("<--------")
