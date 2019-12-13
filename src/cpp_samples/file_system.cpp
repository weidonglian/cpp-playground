#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

int main(int argc, char** argv) {
    path pathToShow("../");
    cout << "exists() = " << exists(pathToShow) << "\n"
         << "root_name() = " << pathToShow.root_name() << "\n"
         << "root_path() = " << pathToShow.root_path() << "\n"
         << "relative_path() = " << pathToShow.relative_path() << "\n"
         << "parent_path() = " << pathToShow.parent_path() << "\n"
         << "filename() = " << pathToShow.filename() << "\n"
         << "stem() = " << pathToShow.stem() << "\n"
         << "extension() = " << pathToShow.extension() << "\n";
    for (auto& p : recursive_directory_iterator("."))
        cout << "item:" << p.path() << endl;
    return 0;
}