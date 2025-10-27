#pragma once

#include <zen/zen_pch.h>

namespace Zen {
  using json = nlohmann::json;

  struct ProfileResult {
    const char *name;
    uint32_t threadId;
    long long start;
    long long end;
  };

  struct ProfilerSession {
    const char *name;
  };

  class Profiler {
  public:
    static Profiler &get() {
      static Profiler instance;
      return instance;
    };

    void startSession(const char *sessionName, const char *filePath = "sessionResults.json") {
      if (m_isActive)
        endSession();

      m_outputStream.open(filePath);

      m_sessionName = sessionName;
      m_isActive    = true;
    };

    void endSession() {
      if (!m_isActive)
        return;

      m_isActive              = false;
      m_events["traceEvents"] = m_results;

      m_outputStream << m_events;
      m_outputStream.close();
      m_results.clear();
    };

    void writeProfile(const ProfileResult &result) {
      json res;

      res["name"] = result.name;
      res["cat"]  = "function";
      res["ph"]   = "X"; // Event Type: Complete
      res["ts"]   = result.start;
      res["dur"]  = (result.end - result.start);
      res["pid"]  = 0;
      res["tid"]  = result.threadId;

      m_results.emplace_back(res);
    };

  private:
    Profiler() {
      // HACK: Arbitrary number of results to reserve
      m_results.reserve(2048);
      m_events["displayTimeUnit"] = "ms";
      m_events["otherData"]       = {"profile", "Debug"};
    };

    ~Profiler() {
      if (m_isActive) {
        endSession();
      };
    };

    std::ofstream m_outputStream;

    json m_events;
    std::vector<json> m_results{};

    ProfilerSession *m_currentSession{nullptr};
    std::string m_sessionName = "NULL";
    bool m_isActive;
  };

  class ProfilerTimer {
  public:
    explicit ProfilerTimer(const char *name) {
      m_startTimePoint = std::chrono::high_resolution_clock::now();
      m_result.name    = name;
      m_result.start   = 0;
      m_result.end     = 0;
      m_isFinished     = false;
    };

    ~ProfilerTimer() {
      if (!m_isFinished)
        stop();
    };

    void stop() {
      const auto endTimePoint = std::chrono::high_resolution_clock::now();

      m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint)
                           .time_since_epoch()
                           .count();

      m_result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint)
                         .time_since_epoch()
                         .count();

      m_result.threadId = std::hash<std::thread::id>()(std::this_thread::get_id());

      Profiler::get().writeProfile(m_result);

      m_isFinished = true;
    };

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
    ProfileResult m_result;
    bool m_isFinished;
  };
}; // namespace Zen
