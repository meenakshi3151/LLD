#include <bits/stdc++.h>
using namespace std;

#define URL_SIZE 8
#define URL_TTL 30   // days

class URLHandler {
private:
    unordered_map<string, string> shortToLong;
    unordered_map<string, time_t> createdAt;

    string generateRandomString(int length) {
        static const string chars =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dist(0, chars.size() - 1);

        string s;
        for (int i = 0; i < length; i++)
            s += chars[dist(gen)];
        return s;
    }

    bool isExpired(time_t t) {
        time_t now = time(nullptr);
        return difftime(now, t) > URL_TTL * 24 * 60 * 60;
    }

public:
    string generateURL(const string& longURL) {
        string shortURL;
        do {
            shortURL = generateRandomString(URL_SIZE);
        } while (shortToLong.count(shortURL));

        shortToLong[shortURL] = longURL;
        createdAt[shortURL] = time(nullptr);
        return shortURL;
    }

    string generateURL(const string& longURL, const string& customShortURL) {
        if (shortToLong.count(customShortURL))
            throw runtime_error("Custom short URL already exists");

        shortToLong[customShortURL] = longURL;
        createdAt[customShortURL] = time(nullptr);
        return customShortURL;
    }

    string redirect(const string& shortURL) {
        if (!shortToLong.count(shortURL))
            throw runtime_error("Short URL not found");

        if (isExpired(createdAt[shortURL])) {
            shortToLong.erase(shortURL);
            createdAt.erase(shortURL);
            throw runtime_error("URL expired");
        }

        return shortToLong[shortURL];
    }

    void displayURLDetails(const string& shortURL) {
        if (!shortToLong.count(shortURL)) {
            cout << "URL not found\n";
            return;
        }

        cout << "\nShort URL  : " << shortURL << endl;
        cout << "Long URL   : " << shortToLong[shortURL] << endl;
        cout << "Created At : " << ctime(&createdAt[shortURL]);
        cout << "-----------------------------\n";
    }

    void destroyExpiredURLs() {
        vector<string> toDelete;

        for (auto& it : createdAt) {
            if (isExpired(it.second))
                toDelete.push_back(it.first);
        }

        for (auto& key : toDelete) {
            shortToLong.erase(key);
            createdAt.erase(key);
        }

        cout << "Expired URLs cleaned up\n";
    }
};

void showMenu() {
    cout << "\n====== URL Shortener CLI ======\n";
    cout << "1. Generate Short URL\n";
    cout << "2. Generate Custom Short URL\n";
    cout << "3. Redirect Short URL\n";
    cout << "4. Show URL Details\n";
    cout << "5. Cleanup Expired URLs\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    URLHandler handler;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;
        cin.ignore();

        try {
            if (choice == 1) {
                string longURL;
                cout << "Enter long URL: ";
                getline(cin, longURL);

                string shortURL = handler.generateURL(longURL);
                cout << "Generated Short URL: " << shortURL << endl;
            }
            else if (choice == 2) {
                string longURL, custom;
                cout << "Enter long URL: ";
                getline(cin, longURL);
                cout << "Enter custom short URL: ";
                getline(cin, custom);

                string shortURL = handler.generateURL(longURL, custom);
                cout << "Generated Custom Short URL: " << shortURL << endl;
            }
            else if (choice == 3) {
                string shortURL;
                cout << "Enter short URL: ";
                getline(cin, shortURL);

                cout << "Redirecting to: "
                     << handler.redirect(shortURL) << endl;
            }
            else if (choice == 4) {
                string shortURL;
                cout << "Enter short URL: ";
                getline(cin, shortURL);

                handler.displayURLDetails(shortURL);
            }
            else if (choice == 5) {
                handler.destroyExpiredURLs();
            }
            else if (choice == 6) {
                cout << "Exiting...\n";
                break;
            }
            else {
                cout << "Invalid choice\n";
            }
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
