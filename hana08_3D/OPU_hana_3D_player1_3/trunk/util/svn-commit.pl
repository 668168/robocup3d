#!/usr/bin/perl

use Cwd;

my $path = getcwd;

if ($#ARGV == 0) {
  $path = $ARGV[0];
}


my @yesExps;
my @noExps;

sub loadTab {
  open (TAB, "svn-commit.tab");
  while ($line = <TAB>) {
    ($ayOrNay, $exp) = split(/\s+/, $line);
    $exp =~ s/\./\\\./g;
    $exp =~ s/\*/\.*/g;
    $exp =~ s/^\//\(\\\/\|\^\)/;
    if ($exp !~ /\$$/) {
      $exp .= "\$";
    }
    
    print "$ayOrNay $exp\n";
    
    if ($ayOrNay eq "+") {
      push @yesExps, $exp;
    } elsif ($ayOrNay eq "-") {
      push @noExps, $exp;
    }
  }
}

sub ay
{
  my $file = pop;
  foreach $yesExp (@yesExps) {
    if ($file =~ /$yesExp/) {
      return 1;
    }
  }
  return 0;
}

sub nay
{
  my $file = pop;
  foreach $noExp (@noExps) {
    if ($file =~ /$noExp/) {
      return 1;
    }
  }
  return 0;
}

sub checkStatus {
  my $svncmd = "svn stat $path | egrep \"^\\?.*".'$'."\" |";
  print "$svncmd\n";
  open(SVNSTAT, $svncmd);

  while ($line = <SVNSTAT>) {
    my ($state, $file) = split(/\s+/, $line);
    chomp $file;

    if (-d $file && !nay($file)) {
      print "New directory: $file. Add?\n(y)es/(n)o ";
      my $answer = <STDIN>;
      chomp $answer;
      if ($answer eq "y") {
        system("svn add $file -N");
        print "Restarting...\n\n";
        checkStatus();
        return;
      } else {
        push @noExps, "^$file\$";
      }
    }
    else
    {
      my $base = `basename $file`;
      chomp $base;
      my @dummy = split(/\./, $base);
      my $extention = pop @dummy;
      if ($extention ne $base && ay($file)) {
        system("svn add $file");
      }
      elsif($extention ne $base && !nay($file))
      {
        print "New file: $file. Add?\n(y)es/(n)o/(Y)es for this extention ($extention)/(N)o for this extention ";
        my $answer = <STDIN>;
        chomp $answer;
        if ($answer eq "y") {
          system("svn add $file");
        } elsif ($answer eq "Y") {
          system("svn add $file");
          push @yesExps, ".*\.".$extention."\$";
        } elsif ($answer eq "N") {
          push @noExps, ".*\.".$extention."\$";
        }

      }
    }        
  }
}

print "Loading table...\n";
loadTab;

print "Checking status...\n";
checkStatus;

exec("svn ci $path");
