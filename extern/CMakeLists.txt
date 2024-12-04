# Enable FetchContent.
include(FetchContent)

# Enable ExternalProject
include(ExternalProject)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
    
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF)
FetchContent_MakeAvailable(googletest)

# Fetch Highs.
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    highs
    URL https://github.com/ERGO-Code/HiGHS/archive/refs/tags/v1.7.2.zip
    EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(highs)



# Based on https://github.com/fontanf/mathoptsolverscmake/blob/main/extern/CMakeLists.txt
# Errors to fix when using "cmake .." in the /build rep.

add_library(dominating_set_ORtools INTERFACE)

ExternalProject_Add(ORtools
    URL https://github.com/google/or-tools/releases/download/v9.11/or-tools_amd64_ubuntu-24.04_cpp_v9.11.4210.tar.gz
    URL_HASH SHA256=71761d93171b111fca736647a6cd00cb9e606474df597a8b48f3f5f2c73d4c0f
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND "")
target_include_directories(dominating_set_ORtools INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}/ortools-prefix/src/ortools/include")
target_link_directories(dominating_set_ORtools INTERFACE
    "${CMAKE_CURRENT_BINARY_DIR}/ortools-prefix/src/ortools/lib")
target_link_libraries(dominating_set_ORtools INTERFACE
    libabsl_bad_any_cast_impl.a
    libabsl_bad_optional_access.a
    libabsl_bad_variant_access.a
    libabsl_base.a
    libabsl_city.a
    libabsl_civil_time.a
    libabsl_cord.a
    libabsl_cord_internal.a
    libabsl_cordz_functions.a
    libabsl_cordz_handle.a
    libabsl_cordz_info.a
    libabsl_cordz_sample_token.a
    libabsl_crc32c.a
    libabsl_crc_cord_state.a
    libabsl_crc_cpu_detect.a
    libabsl_crc_internal.a
    libabsl_debugging_internal.a
    libabsl_decode_rust_punycode.a
    libabsl_demangle_internal.a
    libabsl_demangle_rust.a
    libabsl_die_if_null.a
    libabsl_examine_stack.a
    libabsl_exponential_biased.a
    libabsl_failure_signal_handler.a
    libabsl_flags_commandlineflag.a
    libabsl_flags_commandlineflag_internal.a
    libabsl_flags_config.a
    libabsl_flags_internal.a
    libabsl_flags_marshalling.a
    libabsl_flags_parse.a
    libabsl_flags_private_handle_accessor.a
    libabsl_flags_program_name.a
    libabsl_flags_reflection.a
    libabsl_flags_usage.a
    libabsl_flags_usage_internal.a
    libabsl_graphcycles_internal.a
    libabsl_hash.a
    libabsl_hashtablez_sampler.a
    libabsl_int128.a
    libabsl_kernel_timeout_internal.a
    libabsl_leak_check.a
    libabsl_log_entry.a
    libabsl_log_flags.a
    libabsl_log_globals.a
    libabsl_log_initialize.a
    libabsl_log_internal_check_op.a
    libabsl_log_internal_conditions.a
    libabsl_log_internal_fnmatch.a
    libabsl_log_internal_format.a
    libabsl_log_internal_globals.a
    libabsl_log_internal_log_sink_set.a
    libabsl_log_internal_message.a
    libabsl_log_internal_nullguard.a
    libabsl_log_internal_proto.a
    libabsl_log_severity.a
    libabsl_log_sink.a
    libabsl_low_level_hash.a
    libabsl_malloc_internal.a
    libabsl_periodic_sampler.a
    libabsl_poison.a
    libabsl_random_distributions.a
    libabsl_random_internal_distribution_test_util.a
    libabsl_random_internal_platform.a
    libabsl_random_internal_pool_urbg.a
    libabsl_random_internal_randen.a
    libabsl_random_internal_randen_hwaes.a
    libabsl_random_internal_randen_hwaes_impl.a
    libabsl_random_internal_randen_slow.a
    libabsl_random_internal_seed_material.a
    libabsl_random_seed_gen_exception.a
    libabsl_random_seed_sequences.a
    libabsl_raw_hash_set.a
    libabsl_raw_logging_internal.a
    libabsl_scoped_set_env.a
    libabsl_spinlock_wait.a
    libabsl_stacktrace.a
    libabsl_status.a
    libabsl_statusor.a
    libabsl_string_view.a
    libabsl_symbolize.a
    libabsl_synchronization.a
    libabsl_throw_delegate.a
    libabsl_time.a
    libabsl_time_zone.a
    libabsl_utf8_for_code_point.a
    libabsl_vlog_config_internal.a
    libCbc.a
    libCbcSolver.a
    libCgl.a
    libClp.a
    libClpSolver.a
    libCoinUtils.a
    libOsi.a
    libOsiCbc.a
    libOsiClp.a
    libprotobuf.a
    libprotobuf-lite.a
    libprotoc.a
    libre2.a
    libscip.a
    libutf8_range.a
    libutf8_validity.a
    libz.a)

add_dependencies(dominating_set_ORtools ortools)