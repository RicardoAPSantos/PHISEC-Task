//QUICK EXPLANATION:
//Running the program will ask you to write the news and then will ask you to choose
//which sponsor tier do you want to send it too. Then it will see your answer and 
//create an "email" to every sponsor that have the tier selected. This have a random
//chance to give different status to every email to simulate the status system


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==========================================================
// CLASSE CLIENT (H + CPP)
// ==========================================================
class Client {
public:
    enum Department { AERODYNAMICS, SOCIAL, PILOT, OTHER };
    Client(string name, string email, Department d);
    int getId() const;
    string getName() const;
    string getEmail() const;
    Department getDepartment() const;
    string toString() const;
private:
    static int id_Global_Client;
    const int id;
    const string name;
    const string email;
    const Department department;
};

int Client::id_Global_Client = 1;

Client::Client(string name, string email, enum Department d)
    : id(id_Global_Client++), name(name), email(email), department(d) {}

int Client::getId() const { return id; }
string Client::getName() const { return name; }
string Client::getEmail() const { return email; }
enum Client::Department Client::getDepartment() const { return department; }

string Client::toString() const {
    string department_str;
    switch(department) {
        case AERODYNAMICS: department_str = "AERODYNAMICS"; break;
        case SOCIAL: department_str = "SOCIAL"; break;
        case PILOT: department_str = "PILOT"; break;
        case OTHER: department_str = "OTHER"; break;
    }
    ostringstream oss;
    oss << "Client " << name << " [id=" << id << ", email=" << email
        << ", department=" << department_str << "]";
    return oss.str();
}

// ==========================================================
// CLASSE SPONSOR (H + CPP)
// ==========================================================
class Sponsor {
public:
    enum Tier { SILVER, GOLD, PLATINUM };
    Sponsor(string name, string email, Tier t);
    ~Sponsor();
    int get_id() const;
    string get_name() const;
    string get_email() const;
    string get_tier() const;
    string toString() const;
private:
    static int id_Global_Sponsor;
    const int id;
    const string name;
    const string email;
    const Tier tier;
};

int Sponsor::id_Global_Sponsor = 1;

Sponsor::Sponsor(string name, string email, enum Tier t)
    : id(id_Global_Sponsor++), name(name), email(email), tier(t) {}

Sponsor::~Sponsor() {}
int Sponsor::get_id() const { return id; }
string Sponsor::get_name() const { return name; }
string Sponsor::get_email() const { return email; }

string Sponsor::get_tier() const {
    if (this->tier == SILVER) return "SILVER";
    if (this->tier == GOLD) return "GOLD";
    return "PLATINUM";
}

string Sponsor::toString() const {
    string tier_str;
    switch(tier) {
        case SILVER:   tier_str = "SILVER";   break;
        case GOLD:     tier_str = "GOLD";     break;
        case PLATINUM: tier_str = "PLATINUM"; break;
    }
    ostringstream oss;
    oss << "Sponsor " << name << " [id=" << id << ", email=" << email
        << ", tier=" << tier_str << "]";
    return oss.str();
}

// ==========================================================
// CLASSE EMAIL (H + CPP)
// ==========================================================
class Email {
public:
    enum Status { WAITING, SUCCESS, ERROR };
    Email();
    string toString();
private:
    static int id_Global_Email;
    const int id;
    Status status;
};

int Email::id_Global_Email = 1;

Email::Email() : id(id_Global_Email++), status(WAITING) {
    int x = rand() % 3; // Gera 0, 1 ou 2
    if (x == 0) this->status = WAITING;
    else if (x == 1) this->status = SUCCESS;
    else this->status = ERROR;
}

string Email::toString() {
    string status_str;
    switch(status) {
        case WAITING: status_str = "WAITING"; break;
        case SUCCESS: status_str = "SUCCESS"; break;
        case ERROR: status_str = "ERROR"; break;
    }
    ostringstream oss;
    oss << "Email id: " << id << ", status= " << status_str << "]";
    return oss.str();
}

// ==========================================================
// FUNÇÕES AUXILIARES E MAIN
// ==========================================================
void send_email(const string & news, Client * client, Sponsor * sponsor) {
    cout << "email from: " << client->getEmail() << endl
         << "to: " << sponsor->get_email() << endl
         << "message: \nHi " << sponsor->get_name() << endl << endl
         << news << endl << endl
         << "Best regards, " << client->getName() << endl
         << "==========================" << endl;

    Email* email = new Email();
    cout << email->toString() << endl
         << "==========================" << endl;
}

int main() {
    srand(time(0));

    Client* client1 = new Client("PHISEC", "phisec@gmail.com", Client::OTHER);

    Sponsor* sponsor1 = new Sponsor("RedBull", "redbull@gmail.com", Sponsor::PLATINUM);
    Sponsor* sponsor2 = new Sponsor("ISEC", "isec@gmail.com", Sponsor::GOLD);
    Sponsor* sponsor3 = new Sponsor("ESEC", "esec@gmail.com", Sponsor::GOLD);
    Sponsor* sponsor4 = new Sponsor("LIDL", "lidl@gmail.com", Sponsor::GOLD);

    vector<Sponsor*> sponsors = {sponsor1, sponsor2, sponsor3, sponsor4};

    string news;
    string tier_aux;

    cout << "Write the news: " << endl;
    getline(cin, news); // Usar getline para permitir espaços nas notícias

    cout << "Which sponsors (SILVER, GOLD, PLATINUM,ALL): " << endl;
    cin >> tier_aux;


    transform(tier_aux.begin(), tier_aux.end(), tier_aux.begin(), ::toupper);

    int cont = 0;
    for(size_t i = 0; i < sponsors.size(); i++) {
        if (tier_aux == "ALL") {
            send_email(news, client1, sponsors.at(i));
            cont++;
        }
        else if (tier_aux == sponsors.at(i)->get_tier()) {
            send_email(news, client1, sponsors.at(i));
            cont++;
        }
    }

    cout << "Emails sent: " << cont << endl << endl;

    cout << "--- FINAL DATA ---" << endl;
    cout << client1->toString() << endl;
    for (Sponsor* s : sponsors) {
        cout << s->toString() << endl;
    }

    delete client1;
    for(Sponsor* s : sponsors) delete s;

    return 0;
}
