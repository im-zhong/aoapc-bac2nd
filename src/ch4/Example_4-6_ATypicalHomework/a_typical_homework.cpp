// 2025/4/2
// zhangzhong

#include <array>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// NICE! 为美中特定的类型定义具体的类型别名的好处这就体现出来了
// 最起码有两个好处
// 1. 类型名字，语义更加丰富，我们可以根据类型知道更多的信息
// 2. 如果底层的类型需要修改，改动起来也相对简单！
using sid_t = std::string;

struct SubjectStatistics {
    std::string subject = "";
    int total_score = 0;
    int passed_student_count = 0;
    int failed_student_count = 0;

    std::string ToString() const {
        int total_student_count =
            this->passed_student_count + this->failed_student_count;
        // 这里可能是0啊
        double average_score =
            double(this->total_score) / (total_student_count + 1e-5);

        // 四舍五入
        average_score = std::floor(average_score * 100 + 0.5) / 100;

        std::stringstream ss;
        ss.precision(2);
        ss.setf(std::ios::fixed);
        ss << this->subject << "\n"
           << "Average Score: " << average_score << "\n"
           << "Number of passed students: " << this->passed_student_count
           << "\n"
           << "Number of failed students: " << this->failed_student_count;
        return ss.str();
    }
};

struct OverallStatistics {
    int passed_all_subject_student_count;
    int passed_3_or_more_subjects_student_count;
    int passed_2_or_more_subjects_student_count;
    int passed_1_or_more_subjects_student_count;
    int failed_all_subjects_student_count;

    std::string ToString() const {
        std::stringstream ss;
        ss << "Overall:\n"
           << "Number of students who passed all subjects: "
           << this->passed_all_subject_student_count << "\n"
           << "Number of students who passed 3 or more subjects: "
           << this->passed_3_or_more_subjects_student_count << "\n"
           << "Number of students who passed 2 or more subjects: "
           << this->passed_2_or_more_subjects_student_count << "\n"
           << "Number of students who passed 1 or more subjects: "
           << this->passed_1_or_more_subjects_student_count << "\n"
           << "Number of students who failed all subjects: "
           << this->failed_all_subjects_student_count;
        return ss.str();
    }
};

struct Statistics {
    std::vector<SubjectStatistics> subject_statistics;
    OverallStatistics overall_statistics;

    std::string ToString() {
        std::stringstream ss;
        for (const SubjectStatistics& statistics : this->subject_statistics) {
            ss << statistics.ToString() << "\n\n";
        }
        ss << overall_statistics.ToString();
        return ss.str();
    }
};

struct Student {
    // TODO: 我们需要使用string来保存sid而不是一个字符串
    // 因为有的id里面有前导零 如果用整数来保存 这些0都没了
    // 输出的时候就没有了
    sid_t sid;
    int cid;
    std::string name;
    std::array<int, 4> scores;
    bool tombstone = false;

    // 让map根据总分从高到低排序
    bool operator<(const Student& other) const noexcept {
        return this->GetTotalScore() > other.GetTotalScore();
    }

    static Student ParseLine(const std::string& line) {
        std::stringstream ss{line};
        Student stu;
        ss >> stu.sid >> stu.cid >> stu.name;
        for (int i = 0; i < 4; i++) {
            ss >> stu.scores[i];
        }
        return stu;
    }

    int GetTotalScore() const noexcept {
        int total_score = 0;
        for (const int score : this->scores) {
            total_score += score;
        }
        return total_score;
    }

    double GetAverageScore() const noexcept {
        double total_socre = this->GetTotalScore();
        return total_socre / 4;
    }

    // Note that course scores and total score should be formatted as
    // integers, but average scores should
    // be formatted as a real number with exactly two digits after the decimal
    // point
    std::string ToString(int ranking) const {
        // The format is similar to the input format for “adding a
        // student”, but 3 more columns are added:
        // rank (1st column), total score and average score
        std::stringstream ss;
        // 浮点数在输出时只保留两位小数
        ss.precision(2);
        ss.setf(std::ios::fixed);
        // C++ iostream 用来设置输出格式的方式太垃圾了

        ss << ranking << " " << this->sid << " " << this->cid << " "
           << this->name << " ";
        for (const int score : this->scores) {
            ss << score << " ";
        }
        ss << this->GetTotalScore() << " " << this->GetAverageScore();
        return ss.str();
    }
};

enum Ops {
    EXIT = 0,
    ADD_STUDENT = 1,
    REMOVE_STUDENT = 2,
    QUERY_STUDENT = 3,
    SHOW_RANKLIST = 4,
    SHOW_STATISTICS = 5,
};

class SPMS;

class StudentComparator {
  public:
    StudentComparator(const SPMS& spms) : _spms(spms) {}

    // 不能在这里实现
    // 要到SPMS的后面实现才行
    bool operator()(const sid_t& lhs, const sid_t& rhs) const noexcept;

  private:
    const SPMS& _spms;
};

class SPMS {
  public:
    SPMS() : _comparator(*this), _ranking(_comparator) {}

    std::string GetMainMenu() const {
        return std::string("Welcome to Student Performance "
                           "Management System (SPMS).\n\n") +
               "1 - Add\n" + "2 - Remove\n" + "3 - Query\n" +
               "4 - Show ranking\n" + "5 - Show Statistics\n" + "0 - Exit";
    }

    std::string GetPrompt(Ops op) {
        static const char* prompts[] = {
            "",
            "Please enter the SID, CID, name and four scores. Enter 0 to "
            "finish.",
            "Please enter SID or name. Enter 0 to finish.",
            "Please enter SID or name. Enter 0 to finish.",
            "Showing the ranklist hurts students' self-esteem. Don't do that.",
            "Please enter class ID, 0 for the whole statistics.",

        };
        return prompts[op];
    }

    bool AddStudent(const Student& student) {
        // 现在咱们根据问题的需求，设计一套合理的数据存储方式
        //
        // 首先检查在_sid2index中是否存在sid
        if (this->IsStudentExists(student.sid)) {
            return false;
        }

        this->_stuvec.push_back(student);
        int index = this->_stuvec.size() - 1;
        // 更新索引
        this->_sid2index[student.sid] = index;
        this->_name2indicies[student.name].push_back(index);
        // 而在这里，更新ranking就必须在最后操作
        // 总之ranking的工作需要对应的sid存在
        // 更新ranking
        this->_ranking.insert({student.sid, student.GetTotalScore()});

        assert(this->_ranking.size() == this->_sid2index.size());
        return true;
    }

    bool IsStudentExists(sid_t sid) const {
        // 这里需要考虑索引吗？
        // sid的索引在用户删除的时候是可以进行删除的
        // name的索引不好删，所以才不删，但是hashmap的删除特别好做，所以就删了吧
        return this->_sid2index.count(sid) > 0;
    }

    int RemoveStudentBySID(sid_t sid) {
        if (!this->IsStudentExists(sid)) {
            return 0;
        }

        // 哦 我懂了！
        // 这里我们必须要先删除ranking
        // 因为ranking里面的删除的比较符号需要sid存在的时候才能工作 更新ranking
        this->_ranking.erase(sid);

        int index = this->_sid2index[sid];
        // 删除索引
        // 这里删错了，就应该直接删除索引才对
        this->_sid2index.erase(sid);
        // name索引不进行删除
        // 删除vector
        this->_stuvec[index].tombstone = true;

        assert(this->_ranking.size() == this->_sid2index.size());

        return 1;
    }

    int RemoveStudentByName(const std::string& name) {
        // 循环调用removebysid就行了
        int remove_count = 0;
        for (const int index : this->_name2indicies[name]) {
            Student& student = this->_stuvec[index];
            if (student.tombstone) {
                continue;
            }
            remove_count += this->RemoveStudentBySID(student.sid);
        }
        // 如果是整个名字都被删除的话，对应的索引是可以很容易的删除掉的
        this->_name2indicies[name] = {};
        return remove_count;
    }

    int GetRanking(sid_t sid) {
        // 从前往后遍历_ranking
        // 并记录当前的ranking
        assert(this->IsStudentExists(sid));
        int total = 0;
        int rank = 1;
        int last_score = -1;
        for (auto it = this->_ranking.begin(); it != this->_ranking.end();
             it++) {
            total++;
            int curr_score = it->second;
            if (curr_score == last_score) {
                // 在这种情况下rank不变
            } else {
                rank = total;
            }
            last_score = curr_score;

            if (it->first == sid) {
                break;
            }
        }
        return rank;
    }

    std::vector<Student> QueryStudentsBySID(sid_t sid) const {
        if (!this->IsStudentExists(sid)) {
            return {};
        }

        int index = this->_sid2index.at(sid);
        Student student = this->_stuvec[index];
        assert(!student.tombstone);
        return {student};
    }

    std::vector<Student> QueryStudentsByName(const std::string& name) {
        std::vector<Student> students;
        for (const int index : this->_name2indicies[name]) {
            Student student = this->_stuvec[index];
            if (student.tombstone) {
                continue;
            }
            students.push_back(std::move(student));
        }
        return students;
    }

    std::vector<int> GetStudentsByCID(int cid) const {
        std::vector<int> students;
        for (int i = 0; i < this->_stuvec.size(); i++) {
            const Student& student = this->_stuvec[i];
            if (student.cid == cid && !student.tombstone) {
                students.push_back(i);
            }
        }
        return students;
    }

    Statistics GetStatisticsOfStudents(const std::vector<int>& students) {
        SubjectStatistics subject_statistics[4];
        subject_statistics[0].subject = "Chinese";
        subject_statistics[1].subject = "Mathematics";
        subject_statistics[2].subject = "English";
        subject_statistics[3].subject = "Programming";
        int passed_score = 60;

        // 使用一个数组，统计每个学生pass了多少课程
        std::vector<int> passes;
        for (const int index : students) {
            const Student& student = this->_stuvec[index];
            int passed_count = 0;
            // 分析该学生的各个学科的分数
            for (int i = 0; i < 4; i++) {
                int score = student.scores[i];
                subject_statistics[i].total_score += score;
                if (score >= passed_score) {
                    subject_statistics[i].passed_student_count += 1;
                    passed_count += 1;
                } else {
                    subject_statistics[i].failed_student_count += 1;
                }
            }
            passes.push_back(passed_count);
        }
        // passes记录的就是参数中传入的同学，每个同学过了多少门课
        assert(passes.size() == students.size());

        // 然后统计overall
        // passes = [0, 1, 4, 3, 3, 2, ...]
        // 咱们再创建一个数组
        std::array<int, 5> total_passed_count = {0, 0, 0, 0, 0};
        for (const int passed_count : passes) {
            total_passed_count[passed_count] += 1;
        }
        // 我懂了，这里确实错了
        // 因为他统计的是1 or more
        // 所以应该是整个数组的和才对
        for (int i = 4; i > 1; i--) {
            // [3] = [3] + [4]
            // [2] = [2] + [3] + [4]
            // [1] = [1] + [2] + [3] + [4]
            total_passed_count[i - 1] += total_passed_count[i];
        }

        OverallStatistics overall_statistics{
            total_passed_count[4], total_passed_count[3], total_passed_count[2],
            total_passed_count[1], total_passed_count[0],
        };

        return Statistics{
            std::vector<SubjectStatistics>{
                subject_statistics[0], subject_statistics[1],
                subject_statistics[2], subject_statistics[3]},
            overall_statistics,
        };
    }

    Statistics GetStatisticsOfClass(int cid) {
        // 我们首先根据cid获得students
        std::vector<int> students = this->GetStudentsByCID(cid);
        return this->GetStatisticsOfStudents(students);
    }

    std::vector<int> GetAllStudents() {
        std::vector<int> students;
        for (int i = 0; i < this->_stuvec.size(); i++) {
            const Student& student = this->_stuvec[i];
            if (!student.tombstone) {
                students.push_back(i);
            }
        }
        return students;
    }

    Statistics GetStatisticsOfAllClass() {
        // 首先获得所有的students
        std::vector<int> students = this->GetAllStudents();
        return this->GetStatisticsOfStudents(students);
    }

  private:
    std::vector<Student> _stuvec;
    std::unordered_map<sid_t, int> _sid2index;
    std::unordered_map<std::string, std::vector<int>> _name2indicies;

    // 怎么维护呢？
    // 我们需要删除啊
    StudentComparator _comparator;
    // std::map<sid_t, int, StudentComparator> _ranking;

    std::map<sid_t, int, StudentComparator> _ranking;
};

// 我知道是为什么了
// 因为我们的排序是按照分数来拍的
// 只要分数一样，map就会认为key是一样的，就不会增加一个新的key了
// 这个问题要如何解决呢？
bool StudentComparator::operator()(const sid_t& lhs,
                                   const sid_t& rhs) const noexcept {
    auto students = this->_spms.QueryStudentsBySID(lhs);
    assert(students.size() == 1);
    Student s1 = students.front();

    students = this->_spms.QueryStudentsBySID(rhs);
    assert(students.size() == 1);
    Student s2 = students.front();

    // 为什么分数一样，map就会认为key是重复的呢
    // 为什么只有一个小于函数，map可以知道那些key是重复的呢？
    //     严格弱序关系和等价性
    // std::map使用严格弱序关系(strict weak
    // ordering)来判断键是否相等。在这种数学关系中：
    // 两个元素的等价性通过以下规则确定：
    // 如果!(a < b) 且 !(b < a)为真，则a和b被视为等价
    // 即：既不是a比b小，也不是b比a小，那么它们就是"等价的"
    // 只需要一个小于运算符就可以确定所有可能的关系：
    // a < b：a小于b
    // b < a：b小于a
    // 两者都为假：a和b等价
    // 原来如此，我们可以通过小于符号得到等于的判断，同时又因为map的key是唯一的
    // 所以当我们分数相同的时候，这个同学就存不进去了
    // 解决的方法就是在分数相同的时候，按照sid学号排序
    // 我们有一个multiset 可以用吗？感觉效果是差不多的，
    if (s1.GetTotalScore() == s2.GetTotalScore()) {
        return lhs < rhs;
    }
    return s1.GetTotalScore() > s2.GetTotalScore();
}

void DispatchOp(int op, SPMS& spms, const std::string& line) {
    std::stringstream ss(line);
    switch (op) {
    case ADD_STUDENT: {
        Student stu = Student::ParseLine(line);
        if (!spms.AddStudent(stu)) {
            std::cout << "Duplicated SID.\n";
        }
        break;
    }

    case REMOVE_STUDENT: {
        // 我们仍然要parse line
        // 但是问题是，这可能是一个数字或者是一个字符串
        // 想念pattern match了
        // case Name begins with a capital letter
        // but sid is a digit number
        // os its very easy to distingusi them
        int remove_count = 0;
        if (std::isdigit(line[0])) {
            // read as sid
            sid_t sid;
            ss >> sid;
            remove_count = spms.RemoveStudentBySID(sid);
        } else {
            // read as name
            std::string name;
            ss >> name;
            remove_count = spms.RemoveStudentByName(name);
        }
        std::cout << remove_count << " student(s) removed.\n";
        break;
    }

    case QUERY_STUDENT: {
        // TODO: 这里其实并不需要返回student 只需要返回索引即可
        std::vector<Student> students;
        if (std::isdigit(line[0])) {
            // read as sid
            sid_t sid;
            ss >> sid;
            students = spms.QueryStudentsBySID(sid);
        } else {
            // read as name
            std::string name;
            ss >> name;
            students = spms.QueryStudentsByName(name);
        }
        // 然后输出就行了
        // print out all the matching students, in the same order they’re added
        // to the database
        // The format is similar to the input format for “adding a student”
        // TODO: 还要实现student的ranking 排序
        for (const Student& student : students) {
            std::cout << student.ToString(spms.GetRanking(student.sid)) << "\n";
        }

        break;
    }

    case SHOW_RANKLIST: {
        break;
    }

    case SHOW_STATISTICS: {
        int cid = 0;
        ss >> cid;
        if (cid == 0) {
            std::cout << spms.GetStatisticsOfAllClass().ToString() << "\n\n";
        } else {
            std::cout << spms.GetStatisticsOfClass(cid).ToString() << "\n\n";
        }
        break;
    }

    default: {
        assert(false);
    }
    }
}

int main(int argc, char* argv[]) {

    // input
    // There will be a single test case, ending with a zero entered in the main
    // menu screen

    SPMS spms{};
    while (true) {
        std::cout << spms.GetMainMenu() << "\n\n";

        // 这输入是有问题的
        // 我们只能一行一行的读取，读进来之后再转成整数
        std::string opstr;
        std::getline(std::cin, opstr);
        std::stringstream ss(opstr);
        int op = 0;
        ss >> op;
        if (op == EXIT) {
            break;
        }

        // 这里的处理顺序不对
        // 我们需要提供一个数组，这个数组会根据op来输出prompt
        // 在输出完prompt之后，我们才能getline
        while (true) {
            std::cout << spms.GetPrompt(Ops(op)) << "\n";

            // 如果是4 他都不应该getline的
            if (op == Ops::SHOW_RANKLIST) {
                break;
            }

            std::string line;
            std::getline(std::cin, line);
            // std::stringstream ss(line);
            // 这里有特殊的处理，对于statistics操作
            // 一次只能询问一个cid，输入0不是退出，而是全部的结果
            // 但是我们就不会循环，反而会直接退出
            // 所以这里应该有两个分支
            if (op == Ops::SHOW_STATISTICS) {
                DispatchOp(op, spms, line);
                break;
            } else {
                // 这里的判断出问题了
                // 我们可能不是一个数组，比如在2中，我们的输入可能是一个名字
                // 就是一个字符串 此时是不可能读到数字的
                // 我们需要实现一个strip函数，然后判断整个字符串是不是零
                // substr 第二个参数是size
                // find last not of 返回的是找到的字符的索引 offset
                // 但是size = offset + 1
                if (line.substr(0, line.find_last_not_of(' ') + 1) == "0") {
                    break;
                }
                DispatchOp(op, spms, line);
            }
        }
    }
}
