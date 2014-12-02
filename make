use Cwd;
my $compile="cl /c";
my %component=(
"hardware"=>"Hardware"
);
my $include="";
my $lib="";

sub Compile
{
	my $arg=shift;
	my $currentDir=getcwd;
	not $arc eq "csharp" or $compile=$compile . " /clr *.cpp";
	not $arg eq "lua" 	 or $compile=$compile . " *.cpp";
	$arg=shift;
	die "cannot compile $arg\n" unless exists $component{$arg};
	chdir($component{$arg});
	system($compile);
	chdir($currentDir);
}

sub Link
{
	print "link\n";
}

sub main
{
	my $ARGC=@ARGV;
	die"arg count is zero\n" unless $ARGC!=0;
	my $arg=shift;
	not $arg eq "-c" or Compile(@_) ;
	not $arg eq "-l" or Link(@_);
	print "hello world\n";
}

main(@ARGV);