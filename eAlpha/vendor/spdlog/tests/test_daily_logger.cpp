/*
 * This content is released under the MIT License as specified in
 * https://raw.githubusercontent.com/gabime/spdlog/master/LICENSE
 */
#include "includes.h"

#ifdef SPDLOG_USE_STD_FORMAT
using filename_memory_buf_t = std::basic_string<spdlog::filename_t::value_type>;
#else
using filename_memory_buf_t = fmt::basic_memory_buffer<spdlog::filename_t::value_type, 250>;
#endif

#ifdef SPDLOG_WCHAR_FILENAMES
std::string filename_buf_to_utf8string(const filename_memory_buf_t &w) {
    spdlog::memory_buf_t buf;
    spdlog::details::os::wstr_to_utf8buf(spdlog::wstring_view_t(w.data(), w.size()), buf);
    return SPDLOG_BUF_TO_STRING(buf);
}
#else
std::string filename_buf_to_utf8string(const filename_memory_buf_t &w) {
    return SPDLOG_BUF_TO_STRING(w);
}
#endif

TEST_CASE("daily_logger with dateonly calculator", "[daily_logger]") {
    using sink_type =
        spdlog::sinks::daily_file_sink<std::mutex, spdlog::sinks::daily_filename_calculator>;

    prepare_logdir();

    // calculate filename (time based)
    spdlog::filename_t basename = SPDLOG_FILENAME_T("test_logs/daily_dateonly");
    std::tm tm = spdlog::details::os::localtime();
    filename_memory_buf_t w;
    spdlog::fmt_lib::format_to(std::back_inserter(w), SPDLOG_FILENAME_T("{}_{:04d}-{:02d}-{:02d}"),
                               basename, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    auto logger = spdlog::create<sink_type>("logger", basename, 0, 0);
    for (int i = 0; i < 10; ++i) {
        logger->info("Test message {}", i);
    }
    logger->flush();

    require_message_count(filename_buf_to_utf8string(w), 10);
}

struct custom_daily_file_name_calculator {
    static spdlog::filename_t calc_filename(const spdlog::filename_t &basename, const tm &now_tm) {
        
        return spdlog::fmt_lib::format(SPDLOG_FILENAME_T("{}{:04d}{:02d}{:02d}"),
                                   basename, now_tm.tm_year + 1900, now_tm.tm_mon + 1,
                                   now_tm.tm_mday);        
    }
};

TEST_CASE("daily_logger with custom calculator", "[daily_logger]") {
    using sink_type = spdlog::sinks::daily_file_sink<std::mutex, custom_daily_file_name_calculator>;

    prepare_logdir();

    // calculate filename (time based)
    spdlog::filename_t basename = SPDLOG_FILENAME_T("test_logs/daily_dateonly");
    std::tm tm = spdlog::details::os::localtime();
    filename_memory_buf_t w;
    spdlog::fmt_lib::format_to(std::back_inserter(w), SPDLOG_FILENAME_T("{}{:04d}{:02d}{:02d}"),
                               basename, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    auto logger = spdlog::create<sink_type>("logger", basename, 0, 0);
    for (int i = 0; i < 10; ++i) {
        logger->info("Test message {}", i);
    }

    logger->flush();

    require_message_count(filename_buf_to_utf8string(w), 10);
}

/*
 * File name calculations
 */

TEST_CASE("rotating_file_sink::calc_filename1", "[rotating_file_sink]") {
    auto filename =
        spdlog::sinks::rotating_file_sink_st::calc_filename(SPDLOG_FILENAME_T("rotated.txt"), 3);
    REQUIRE(filename == SPDLOG_FILENAME_T("rotated.3.txt"));
}

TEST_CASE("rotating_file_sink::calc_filename2", "[rotating_file_sink]") {
    auto filename =
        spdlog::sinks::rotating_file_sink_st::calc_filename(SPDLOG_FILENAME_T("rotated"), 3);
    REQUIRE(filename == SPDLOG_FILENAME_T("rotated.3"));
}

TEST_CASE("rotating_file_sink::calc_filename3", "[rotating_file_sink]") {
    auto filename =
        spdlog::sinks::rotating_file_sink_st::calc_filename(SPDLOG_FILENAME_T("rotated.txt"), 0);
    REQUIRE(filename == SPDLOG_FILENAME_T("rotated.txt"));
}

// regex supported only from gcc 4.9 and above
#if defined(_MSC_VER) || !(__GNUC__ <= 4 && __GNUC_MINOR__ < 9)

    #include <regex>

TEST_CASE("daily_file_sink::daily_filename_calculator", "[daily_file_sink]") {
    // daily_YYYY-MM-DD_hh-mm.txt
    auto filename = spdlog::sinks::daily_filename_calculator::calc_filename(
        SPDLOG_FILENAME_T("daily.txt"), spdlog::details::os::localtime());
    // date regex based on https://www.regular-expressions.info/dates.html
    std::basic_regex<spdlog::filename_t::value_type> re(
        SPDLOG_FILENAME_T(R"(^daily_(19|20)\d\d-(0[1-9]|1[012])-(0[1-9]|[12][0-9]|3[01])\.txt$)"));
    std::match_results<spdlog::filename_t::const_iterator> match;
    REQUIRE(std::regex_match(filename, match, re));
}
#endif

TEST_CASE("daily_file_sink::daily_filename_format_calculator", "[daily_file_sink]") {
    std::tm tm = spdlog::details::os::localtime();
    // example-YYYY-MM-DD.log
    auto filename = spdlog::sinks::daily_filename_format_calculator::calc_filename(
        SPDLOG_FILENAME_T("example-%Y-%m-%d.log"), tm);

    REQUIRE(filename ==
            spdlog::fmt_lib::format(SPDLOG_FILENAME_T("example-{:04d}-{:02d}-{:02d}.log"),
                                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday));
}

/* Test removal of old files */
static spdlog::details::log_msg create_msg(std::chrono::seconds offset) {
    using spdlog::log_clock;
    spdlog::details::log_msg msg{"test", spdlog::level::info, "Hello Message"};
    msg.time = log_clock::now() + offset;
    return msg;
}

static void test_rotate(int days_to_run, uint16_t max_days, uint16_t expected_n_files) {
    using spdlog::log_clock;
    using spdlog::details::log_msg;
    using spdlog::sinks::daily_file_sink_st;

    prepare_logdir();

    spdlog::filename_t basename = SPDLOG_FILENAME_T("test_logs/daily_rotate.txt");
    daily_file_sink_st sink{basename, 2, 30, true, max_days};

    // simulate messages with 24 intervals

    for (int i = 0; i < days_to_run; i++) {
        auto offset = std::chrono::seconds{24 * 3600 * i};
        sink.log(create_msg(offset));
    }

    REQUIRE(count_files("test_logs") == static_cast<size_t>(expected_n_files));
}

TEST_CASE("daily_logger rotate", "[daily_file_sink]") {
    int days_to_run = 1;
    test_rotate(days_to_run, 0, 1);
    test_rotate(days_to_run, 1, 1);
    test_rotate(days_to_run, 3, 1);
    test_rotate(days_to_run, 10, 1);

    days_to_run = 10;
    test_rotate(days_to_run, 0, 10);
    test_rotate(days_to_run, 1, 1);
    test_rotate(days_to_run, 3, 3);
    test_rotate(days_to_run, 9, 9);
    test_rotate(days_to_run, 10, 10);
    test_rotate(days_to_run, 11, 10);
    test_rotate(days_to_run, 20, 10);
}
