BEGIN {
count=0;
}
{
if($1=="d")
count  ++
}
END {
printf("The total no of packets Dropped due to congestion %d",count);
}
