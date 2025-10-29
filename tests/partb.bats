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

@test "./build/partb one" {
    run partb one

    assert_output "one"                                  # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}

@test "./build/partb one TWO" {
    run partb one TWO

    assert_output "one TWO"                                  # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "./build/partb one TWO three" {
    run partb one TWO three

    assert_output "TWO"                                # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}
@test "./build/partb one two three four" {
    run partb one two three four

    assert_output "two three"                          # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}

@test "./build/partb one Two Three four five" {
    run partb one Two Three four five
    assert_output "Three"                          # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}

@test "./build/partb one Two THree Four five SIx" {
    run partb one Two THree Four five SIx
    assert_output "THree Four"                          # Assert if output matches
    assert [ "$status" -eq 0 ]                             # Assert if exit status matches
}

@test "partb" {
    run partb

    assert_output "ERROR: No arguments"                    # Assert if output matches
    assert [ "$status" -eq 1 ]                             # Assert if exit status matches
}
