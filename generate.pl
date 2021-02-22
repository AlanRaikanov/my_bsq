#!/usr/bin/perl -w

if ((scalar @ARGV) != 3)
{
  print "program x y density\n";
  exit;
}

my $x = $ARGV[0];
my $y = $ARGV[1];
my $density = $ARGV[2];
my $i = 0;
my $j = 0;
my $filename = "input";

open(FH, '>', $filename) or die $!;

print FH $y . "\n";

while ($i < $y)
{
  $j = 0;
  while ($j < $x)
  {
    if (int(rand($y)*2) < $density)
    {
      print FH "o";
    }
    else
    {
      print FH ".";
    }
    $j++;
  }
  print FH "\n";
  $i++;
}