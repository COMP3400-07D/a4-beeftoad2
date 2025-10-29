setup() {
    if [ -d "/usr/lib/bats" ]; then
        load "/usr/lib/bats/bats-support/load"
        load "/usr/lib/bats/bats-assert/load"
    elif [ -d "/opt/homebrew/lib" ]; then
        load "/opt/homebrew/lib/bats-support/load"
        load "/opt/homebrew/lib/bats-assert/load"
    elif [ -d "/usr/local/lib" ]; then
        load "/usr/local/lib/bats-support/load"
        load "/usr/local/lib/bats-assert/load"
    fi
    export BATS_TEST_TIMEOUT=10

    PATH="$(pwd)/build:$PATH"
}

@test "./build/parta Hello" {
    run parta Hello
    assert_output HELLO
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}

@test "./build/parta HowDY" {
    run parta HowDY
    assert_output HOWDY
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "./build/parta Goodbye" {
    run parta Goodbye
    assert_output GOODBYE
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "./build/parta Hello Goodbye" {
    run parta Hello,Goodbye
    assert_output HELLO,GOODBYE
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "./build/parta a b c d e f" {
    run parta A B C D E F
    assert_output A,B,C,D,E,F
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "parta" {
    run parta

    assert_output "ERROR: No arguments"                    # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}
