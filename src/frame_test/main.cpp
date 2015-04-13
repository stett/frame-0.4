#include "tests/test_frame.h"
#include "tests/test_core.h"
#include "tests/test_component.h"
#include "tests/test_system.h"
#include "tests/test_serialization.h"
#include "tests/test_singleton.h"
#include "tests/test_event.h"
#include "gtest/gtest.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
