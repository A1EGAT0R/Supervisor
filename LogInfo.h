#pragma once

#include <string>
#include <array>

class LogInfo
{
    std::string date_time;
    std::string error_type;
    std::string mess;

public:

    LogInfo(std::string dt_tm, std::string err, std::string plc):
            date_time(std::move(dt_tm)),
            error_type(std::move(err)),
            mess(std::move(plc))
    {}


    LogInfo():
            date_time(""),
            error_type(""),
            mess("")
    {}

    LogInfo(const std::string& logLine)
    {
        std::string members_read[3];
        size_t which_member = 0;

        for (char it: logLine) {
                if(it=='-')
                    which_member++;
                else
                    members_read[which_member]+=it;

                if(which_member>2)
                    break;
        }

        date_time = members_read[0];
        error_type = members_read[1];
        mess = members_read[2];
    }

    std::string getStringFormat() const noexcept
    {return date_time + '-' + error_type + '-' + mess;}

    std::string getTime() const noexcept
    {return date_time;}
    std::string getLevel() const noexcept
    {return error_type;}
    std::string getMess() const noexcept
    {return mess;}
};