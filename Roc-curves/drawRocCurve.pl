#!/usr/bin/perl -w

use strict;


my $GNUPLOT = "/usr/bin/gnuplot";
my $detDir = "./RocCurveCoord/";

sub makeGNUplotFile
{
  my $dir = shift;
  my $gnuplotFile = shift;
  my $title = shift;
  my $pngFile = shift;
  my ($colors, $rocFiles) = @_;

  open(GF, ">$gnuplotFile") or die "Can not open $gnuplotFile for writing\n"; 
  #print GF "$GNUPLOT\n";
  print GF "set term png\n";
  #print GF "set size .75,1\n";
  print GF "set output \"$pngFile\"\n";
  #print GF "set xtics 500\n";
  #print GF "set logscale x\n";
  print GF "set ytics .1\n";
  print GF "set grid\n";
  #print GF "set size ratio -1\n";
  print GF "set ylabel \"True positive rate\"\n";
  print GF "set xlabel \"False positives\"\n";
  print GF "set xr [0:50000]\n";
  print GF "set yr [0:1]\n";
  print GF "set key right bottom\n";
  #print GF "set style line 1 lw 2";
  my $strPlot = "plot ";
  for(my $i = 0; $i < scalar(@$rocFiles); $i++)
  {
  	my $filename = $dir.@$rocFiles[$i];
    $strPlot = $strPlot . "\"$filename\" using 2:1 with lines lt rgb \"@$colors[$i]\" lw 2 title \"@$rocFiles[$i]\", ";
  }
  #print $strPlot."\n";
  print GF $strPlot;
  close(GF);
}

my $gpFile = "createROC.p";
my @colors = ("#FF0000", "#00FF00", "#0000FF", "#FF00FF", "#FFFF00", "#00FFFF",);
my @filesCont = ("ViolaJonesScore_n0_ContROC.txt", "ContROC.txt", "jainContROC.txt", "kienzleContROC.txt", "MikolajczykContROC.txt", "subburamanContROC.txt");
makeGNUplotFile($detDir, $gpFile, "Opencv-VJ-fddb", $detDir."/../VJContROC.png", \@colors, \@filesCont);
system("echo \"load '$gpFile'\" | $GNUPLOT");

my @filesDisc = ("ViolaJonesScore_n0_DiscROC.txt", "DiscROC.txt", "jainDiscROC.txt", "kienzleDiscROC.txt", "MikolajczykDiscROC.txt", "subburamanDiscROC.txt");
makeGNUplotFile($detDir, $gpFile, "Opencv-VJ-fddb", $detDir."/../VJDiscROC.png", \@colors, \@filesDisc);
system("echo \"load '$gpFile'\" | $GNUPLOT");

system("rm", $gpFile);