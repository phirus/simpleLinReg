#include<iostream>
#include<string>
#include<boost/program_options.hpp>

#include"linReg.h"

using namespace std;

int main(int argc, char** argv){


	boost::program_options::options_description desc("Allowed options");
	desc.add_options()
        ("help,h", "produce help message")
        ("input,i", boost::program_options::value<string> (), "specify input file")
        ("output,o", boost::program_options::value<string> (), "specify output file")
        ;
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc,argv,desc),vm);
    boost::program_options::notify(vm);


    if(vm.count("help")){
        cout << desc << endl;
        return 1;
    }

    if (vm.count("input")) {
        cout << "Input file is: " << vm["input"].as<string>() << ".\n" << endl ;
        LinReg lr = readFile(vm["input"].as<string>());
        cout << "a = " << lr.getA() << endl;
        cout << "b = " << lr.getB()<< endl;
        cout << "sigma = " << lr.getSigma() << endl;    

        if (vm.count("output")) {
            lr.writeToFile(vm["output"].as<string>());
            cout << "Output written to " << vm["output"].as<string>() << endl;
        } else cout << "no Output file specified" << endl;

    } else {
    cout << "Input file was not set.\n";
    }
    

return 0;
}
