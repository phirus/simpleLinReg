#include<iostream>
#include<boost/program_options.hpp>

using namespace std;

int main(int argc, char** argv){


	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
        ("help,h", "produce help message")
        ;
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
    boost::program_options::notify(vm);


    if(vm.count("help")){
        cout << desc << endl;
        return 1;
    }
    
std::cout << "Hello World" << std::endl;
return 0;
}
