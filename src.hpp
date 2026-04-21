#include <cstddef>
#include <cstring>
#include <string>
#include <cmath>

class BaseJudger {
public:
    BaseJudger(size_t time_limit, size_t memory_limit, const char* answer)
        : time_limit_(time_limit), memory_limit_(memory_limit), score_(0) {
        if (answer) {
            size_t n = std::strlen(answer);
            answer_ = new char[n + 1];
            std::memcpy(answer_, answer, n + 1);
        } else {
            answer_ = new char[1];
            answer_[0] = '\0';
        }
    }

    virtual void Submit(size_t time, size_t memory, const char* output) = 0;

    size_t GetScore() const { return score_; }

    virtual ~BaseJudger() {
        delete[] answer_;
    };

protected:
    char* answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer(const char* output) const {
        return std::strcmp(answer_, output) == 0;
    }
};


class ICPCJudger : public BaseJudger {
public:
    ICPCJudger(size_t time_limit, size_t memory_limit, const char* answer)
        : BaseJudger(time_limit, memory_limit, answer) {}

    void Submit(size_t time, size_t memory, const char* output) override {
        size_t cur = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            cur = 100;
        }
        if (cur > score_) score_ = cur;
    }
};


class OIJudger : public BaseJudger {
public:
    OIJudger(size_t time_limit, size_t memory_limit, const char* answer)
        : BaseJudger(time_limit, memory_limit, answer), submitted_(false), invalidated_(false) {}

    void Submit(size_t time, size_t memory, const char* output) override {
        if (invalidated_) {
            score_ = 0;
            return;
        }
        if (submitted_) {
            // Multiple submissions -> zero score
            score_ = 0;
            invalidated_ = true;
            return;
        }
        submitted_ = true;

        size_t cur = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            cur = 100;
        }
        score_ = cur; // Only one submission counts
    }

protected:
    bool CheckAnswer(const char* output) const override {
        // Compare ignoring trailing spaces at the end of each line
        auto normalize = [](const char* s) -> std::string {
            std::string res;
            if (!s) return res;
            size_t i = 0;
            while (s[i] != '\0') {
                // collect one line until '\n' or '\0'
                size_t start = i;
                while (s[i] != '\0' && s[i] != '\n') ++i;
                size_t end = i; // [start, end) is the line content
                // trim trailing spaces ' '
                while (end > start && s[end - 1] == ' ') --end;
                res.append(s + start, s + end);
                if (s[i] == '\n') {
                    res.push_back('\n');
                    ++i; // skip '\n'
                }
            }
            return res;
        };

        std::string lhs = normalize(answer_);
        std::string rhs = normalize(output);
        return lhs == rhs;
    }

private:
    bool submitted_;
    bool invalidated_;
};


class SpacialJudger : public BaseJudger {
public:
    SpacialJudger(size_t time_limit, size_t memory_limit,
                  size_t full_score_time, size_t full_score_memory,
                  const char* answer)
        : BaseJudger(time_limit, memory_limit, answer),
          full_score_time_(full_score_time), full_score_memory_(full_score_memory) {}

    void Submit(size_t time, size_t memory, const char* output) override {
        size_t cur = 0;
        if (time <= time_limit_ && memory <= memory_limit_ && CheckAnswer(output)) {
            size_t time_score = 0, mem_score = 0;

            // time score
            if (time <= full_score_time_) {
                time_score = 100;
            } else if (time >= time_limit_) {
                time_score = 0;
            } else if (time_limit_ == full_score_time_) {
                time_score = 0; // degenerate range; but constraints likely avoid this
            } else {
                time_score = static_cast<size_t>((time_limit_ - time) * 100 / (time_limit_ - full_score_time_));
            }

            // memory score
            if (memory <= full_score_memory_) {
                mem_score = 100;
            } else if (memory >= memory_limit_) {
                mem_score = 0;
            } else if (memory_limit_ == full_score_memory_) {
                mem_score = 0;
            } else {
                mem_score = static_cast<size_t>((memory_limit_ - memory) * 100 / (memory_limit_ - full_score_memory_));
            }

            cur = (time_score * mem_score) / 100; // floor by integer division
        }
        if (cur > score_) score_ = cur;
    }

private:
    size_t full_score_time_;
    size_t full_score_memory_;
};
