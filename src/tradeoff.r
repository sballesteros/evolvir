b <- seq(1,10,length=100)
a <- seq(0,200,length=100)

plot(a,5.8*(a-0)/(30+(a-0)),type='l',ylim=c(0,11))
abline(h=5)

plot(a,sqrt(a)/2)
