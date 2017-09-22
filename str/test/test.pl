#!/usr/bin/perl

use strict;
use warnings;

exit 1 if @ARGV != 2; # 引数チェック
&main( $ARGV[0], $ARGV[1] );


sub main {
    my $argv1 = shift;
    my $argv2 = shift;

    exit 1 if not &check_argument( $argv1, $argv2 );
    &make_google_test( $argv1, $argv2 );

}



#--------------#
# sub routines #
#--------------#

##
# Google Testをコンパイルする
#
sub make_google_test {
    my $test = shift;
    my $testcode = shift;
    my $make_command = "";

    if( $test eq "test" ) {
        $make_command = &set_command_google_test( $testcode );
    } elsif( $test eq "mock" ) {
        $make_command = &set_command_google_mock( $testcode );
    } else {
        die $!;
    }

    print "$make_command\n\n";

    system $make_command;

    exit 2 if not -f 'a.exe';

    system './a.exe';
}

sub set_command_google_test {
    my $testcode = shift;

    my $code_it_tests = &get_code_it_tests( $testcode );

    my $command = "g++ ../app/$code_it_tests $testcode gtest_main.o gtest-all.o";
    $command .= " -I. -I.. -I../googletest/googletest/include";

    return $command;
}

sub set_command_google_mock {
    my $testcode = shift;

    my $code_it_tests = &get_code_it_tests( $testcode );

    my $command = "g++ ../app/$code_it_tests $testcode gmock_main.o gmock-all.o gtest-all.o";
    $command .= " -I. -I.. -I../googletest/googletest/include -I../googletest/googlemock/include";

    return $command;
}

sub get_code_it_tests {
    my $testcode = shift;

    $testcode =~ /(.\/)?(.+)Test\.cpp/;

    return $2 . ".cpp";
}

##
# 引数がこのプログラムで正しいかどうか確認する
#
sub check_argument {
    my $argv1 = shift;
    my $argv2 = shift;
    my $answer = 1;

    $answer = 0 if $argv1 ne "test" and $argv1 ne "mock";
    $answer = 0 if not &search_testcode( $argv2 );

    return $answer;
}

##
# ファイルがディレクトリ直下に存在するか確認する
#
sub search_testcode {
    my $testcode = shift;
    my $exists_testcode = 1;

    $exists_testcode = 0 if not -f $testcode;
    $exists_testcode = 0 if index( $testcode, "Test" ) <= 0;

    return $exists_testcode;
}
