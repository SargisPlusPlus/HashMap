#include "PrintHash.hpp"
#include "HashMap.hpp"
#include "sstream"
#include "iostream"

PrintHash::PrintHash()
: debug(false)
{
}

void PrintHash::print(HashMap &Hashy)
{
    while(input != "QUIT")
    {
        getline(std::cin, line);
        std::istringstream i(line);
        if (!(i >> input))
        {
            input = "empty";
        }
        if (!(i >> key))
        {
            key = "empty";
        }
        if (!(i >> value))
        {
            value = "empty";
        }

        if(input == "CREATE")
        {
            if(!Hashy.contains(key))
            {
                Hashy.add(key,value);
                std::cout << "CREATED" <<std::endl;
            }
            else if (Hashy.contains(key))
            {
                std::cout << "EXISTS" << std::endl;
            }
        }

        else if (input == "LOGIN" && key != "COUNT")
        {
            if (value == Hashy.value(key))
            std::cout << "SUCCEEDED" << std::endl;
            else if (value != Hashy.value(key))
            std::cout << "FAILED"<<std::endl;
        }

            else if (input == "REMOVE")
        {
        if (Hashy.contains(key))
        {
            Hashy.remove(key);
            std::cout << "REMOVED" << std::endl;
        }
        else if (!Hashy.contains(key))
            std::cout << "NONEXISTENT" << std::endl;
        }

        else if (input == "CLEAR")
        {
            Hashy.clear();
            std::cout <<  "CLEARED" << std::endl;
        }

        else if ((input + " " + key) == "DEBUG ON")
        {
            if (debug == true)
                std::cout << "ON ALREADY" << std::endl;
            else
            {
                debug = true;
                std::cout << "ON NOW" << std::endl;
            }
        }       

        else if ((input + " " + key) == "DEBUG OFF")
        {
            if (debug == false)
                std::cout << "OFF ALREADY" << std::endl;
            else
            {
                debug = false;
                std::cout << "OFF NOW"<< std::endl;
            }
        }

        else if ((input + " " + key) == "LOGIN COUNT")
        {
            if(debug == true)
            {
                int count = Hashy.size();
                std::cout << count << std::endl;
            }
            else
                std::cout << "INVALID" <<std::endl;
         }


         else if ((input + " " + key) == "BUCKET COUNT")
         {
                if(debug == true)
                {
                    int count = Hashy.bucketCount();
                    std::cout << count << std::endl;
                }
                else
                    std::cout << "INVALID"<<std::endl;
         }


        else if ((input + " " + key) == "LOAD FACTOR")
        {
            if(debug == true)
            {
                double count = Hashy.loadFactor();
                std::cout << count << std::endl;
            }
            else
                 std::cout << "INVALID"<<std::endl;
        }

        else if ((input + " " + key + " " + value) == "MAX BUCKET SIZE")
        {
            if(debug == true)
            {
                int count = Hashy.maxBucketSize();
                std::cout << count << std::endl;
            }
            else
                 std::cout << "INVALID"<<std::endl;
         }

        else if (input == "QUIT")
            std::cout<< "GOODBYE!"<<std::endl;

        else
            std::cout <<"INVALID" <<std::endl; 

    }
}
