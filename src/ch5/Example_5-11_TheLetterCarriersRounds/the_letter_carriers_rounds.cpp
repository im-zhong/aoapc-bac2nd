// 2025/4/3
// zhangzhong
// 所以找到题其实就是模拟实现一个SMTP协议
// https://www.reddit.com/r/selfhosted/comments/m6ympg/is_building_a_simple_smtp_email_server_that/
// https://blog.thelifeofkenneth.com/2012/06/minimalist-c-smtp-mail-server.html

// Message Transfer Agent (MTA)
// The sender’s User Agent gives a formatted message to the sending Message
// Transfer Agent(MTA)
// The sending MTA communicates with the receiving MTA using the Simple
// Mail Transfer Protocol (SMTP).

// sender User Agent -> sender MTA --STPM-- receiver MTA -> receiver User Agent

// SMTP handles sending mail between servers
// POP3 or IMAP protocols handle retrieving email from servers
// MIME extends SMTP to support attachments and non-ASCII text

// STMP servers use TCP to connect
// after a communication link is initialize,
// the sending MTA transmits command lines, one at a time, to the receiving MTA,
// which returns a three-digit coded response after each command is processed

// The sender commands are shown below in the order sent for each message
// 1. There is more than one RCPT TO line when the same message is sent to
// several users at the same MTA
// 2. A message to users at different MTAs requires separate SMTP sessions.

// sender command
// HELO myname
// MAIL FROM
// RCPT TO
// DATA
// QUIT

// receiving response code
// 221
// 250
// 354
// 550: message recipients may not exist at the destination MTA. Action not
// taken; no such user here (after RCPT TO with unknown user)

#include <cassert>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::pair<std::string, std::string>
ParseIdentifier(const std::string& identifier) {
    int offset = identifier.find('@');
    return {
        identifier.substr(0, offset),
        identifier.substr(offset + 1),
    };
}

void SimulateSMTP(
    const std::string& sender_mta, const std::string& sender_user,
    const std::string& receiver_mta,
    const std::vector<std::string>& receiver_uesrs,
    const std::vector<std::string>& data,
    const std::unordered_map<std::string, std::set<std::string>>& MTAs) {

    // 因为这里的实现非常简单，我们设置不需要模拟真正的客户端和服务端
    // 只需要模拟这个输出的流程就行了

    // 这里需要做一些检查
    // 检查，我们在外面做吧，这里做的就是单纯的模拟，耦合性更低

    std::string space = "     ";

    std::cout << "Connection between " << sender_mta << " and " << receiver_mta
              << "\n";

    std::cout << space << "HELO " << sender_mta << "\n";
    std::cout << space << "250\n";

    std::cout << space << "MAIL FROM:<" << sender_user << "@" << sender_mta
              << ">\n";
    std::cout << space << "250\n";

    int correct_receiver_count = 0;
    // 有了，我们使用一个set来记录已经发送过的人就好了
    std::unordered_set<std::string> already_sended_receivers;
    for (const std::string& receiver_user : receiver_uesrs) {

        if (already_sended_receivers.count(receiver_user) != 0) {
            continue;
        }
        already_sended_receivers.insert(receiver_user);

        std::cout << space << "RCPT TO:<" << receiver_user << "@"
                  << receiver_mta << ">\n";
        // 这里需要处理unknown user
        //
        if (MTAs.at(receiver_mta).count(receiver_user) == 0) {
            std::cout << space << "550\n";
        } else {
            correct_receiver_count += 1;
            std::cout << space << "250\n";
        }
    }

    // 这个段不是一定会输出的
    // 如果没有需要处理的receiver，就不输出DATA段
    // DATA
    if (correct_receiver_count > 0) {
        std::cout << space << "DATA\n";
        std::cout << space << "354\n";
        for (const std::string& line : data) {
            std::cout << space << line << "\n";
        }
        std::cout << space << "250\n";
    }

    // QUIT
    std::cout << space << "QUIT\n";
    std::cout << space << "221\n";
}

int main(int argc, char* argv[]) {
    // The input contains descriptions of MTAs followed by an arbitrary number
    // of messages

    // 1. MTA
    // MTA, name, numbers of users, list of users
    // * means terminated

    std::unordered_map<std::string, std::set<std::string>> MTAs;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line[0] == '*') {
            break;
        }

        // MTA London 4 Fiona Paul Heather Nevil
        std::stringstream ss{line};

        std::string mta_name;
        ss >> mta_name >> mta_name;

        int user_count = 0;
        ss >> user_count;

        std::set<std::string> users;
        for (int i = 0; i < user_count; i++) {
            std::string user_name;
            ss >> user_name;
            users.insert(user_name);
        }

        MTAs[mta_name] = users;
    }

    // 2. arbitrary number of messages
    // Each message begins with the sending user’s name and is followed by a
    // list of recipient identifiers.
    // Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
    // sender, receiver list, user@mtaname
    // message begins and terminates with an *
    // *
    // message data sender to receiver
    // *

    while (std::getline(std::cin, line)) {
        if (line[0] == '*') {
            break;
        }

        // 首先会读到一行 sender receiver list
        // Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
        // std::getline(std::cin, line);
        std::stringstream ss{std::move(line)};

        std::string sender_identifier;
        ss >> sender_identifier;

        std::vector<std::string> receivers;
        std::string receiver;
        while (ss >> receiver) {
            receivers.push_back(std::move(receiver));
        }

        // 然后就是读取信息了
        // *
        // Hamdy@Cairo Conrado@MexicoCity Shariff@SanFrancisco Lisa@MexicoCity
        // *

        std::getline(std::cin, line);
        assert(line[0] == '*');

        std::vector<std::string> data;
        while (std::getline(std::cin, line)) {
            if (line[0] == '*') {
                break;
            }

            data.push_back(std::move(line));
        }
        data.push_back(".");

        // 我们写一个简单的函数
        // 我们每次simulate的时候，都只传入一个receiver 和 sender
        // 然后一系列的receiptant
        // 这样这个simulate函数实现起来就非常简单

        // 但是我们还要在这里处理，receiptant
        // 因为调度的顺序是mta的出现顺序
        // 所以我们遍历receiver
        std::vector<std::vector<std::string>> index2receivers;
        std::unordered_map<std::string, int> mta2index;
        // 卧槽，我们还需要反过来查，也就是通过索引查找mta的名字
        // 为了方便，我们把mta的名字放到index2receivers的第一个位置吧
        for (const std::string& receiver : receivers) {
            // 然后我们需要组织一个 vector of vector
            // 还需要一个hashmap来保存mta的索引
            // mta 和 receiver user 都需要按照输入顺序类

            // 首先将receiver进行分解
            // receiver = user@mta
            auto pair = ParseIdentifier(receiver);
            const std::string& user = pair.first;
            const std::string& mta = pair.second;

            if (mta2index.count(mta) == 0) {
                index2receivers.push_back({mta});
                int mta_index = index2receivers.size() - 1;
                mta2index[mta] = mta_index;
            }

            // 然后把user放到对应的mta中
            int mta_index = mta2index[mta];
            index2receivers[mta_index].push_back(user);
        }

        // 然后我们只需要遍历index2receivers就好了
        for (int i = 0; i < index2receivers.size(); i++) {
            const std::vector<std::string>& mta_and_receivers =
                index2receivers[i];
            const std::string& receiver_mta = mta_and_receivers[0];
            std::vector<std::string> receiver_users = {
                mta_and_receivers.begin() + 1, mta_and_receivers.end()};
            // 然后剩下的就都是receiver了
            // 咱们在这里调用那个模拟的函数就行了
            auto pair = ParseIdentifier(sender_identifier);

            SimulateSMTP(pair.second, pair.first, receiver_mta, receiver_users,
                         data, MTAs);
        }
    }

    // a extra * terminates all the program

    // output: For each message, show the communication between the sending and
    // receiving MTA

    // protocol
    // 1. A rejection will not affect delivery to authorized users at the
    // same MTA.
    // If there is not at least one authorized recipient at a particular MTA,
    // the DATA is not sent.

    // 2. only one SMTP session is used to send a message to users at a
    // particular MTA, 合理，因为我们知识发给server，从server到user
    // agent还有POP3或者IMAP协议来获取邮件

    // 3. 一次message的传输中，连接MTA的顺序是receiver中的顺序
}