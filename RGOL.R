library('foreach')
library('ggplot2')
library('animation')
library('reshape2')
library('anim.plots')
#install.packages("FFmpeg")
#install.ffmpeg()
#oopts = if (.Platform$OS.type == "windows") {
#ani.options(ffmpeg = "ffmpeg/bin/ffmpeg.exe")
#}
#ffmpeg -i animated.gif -movflags faststart -pix_fmt yuv420p -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" video.mp4
#ffmpeg -i GOL.mp4 -r 160 -filter:v "setpts=0.25*PTS" GOL_speed.mp4

# args:
args = commandArgs(trailingOnly=TRUE)
# test if there is at least one argument: if not, return an error
if (length(args)==0) {
  stop("At least one argument must be supplied (input file).n", call.=FALSE)
}
rep = paste("./",args[1],sep="")
data = paste(rep,args[2],sep="/")
out = paste(rep,args[1],sep="/")
outmp4 = paste(out,"mp4",sep=".")
outmp4speed = paste(paste(out,"speed",sep="_"),"mp4",sep=".")
outgif = paste(out,"gif",sep=".")
cmdmp4 = paste(paste(paste("ffmpeg -i",outmp4,sep=" "),"-r 8 -filter:v setpts=0.025*PTS",sep=" "),outmp4speed,sep=" ")
cmdgif = paste(paste(paste("ffmpeg -i",outmp4speed,sep=" "),"-vf fps=5,scale=450:-1",sep=" "),outgif,sep=" ")
print(data)
print(out)
print(outmp4)
print(outmp4speed)
print(cmdmp4)
print(outgif)
print(cmdgif)
# Converts the current grid (matrix) to a ggplot2 image
grid_to_ggplot <- function(subgrid) {
  subgrid$V <- factor(ifelse(subgrid$V, "Alive", "Dead"))
  #print(subgrid)
  p <- ggplot(subgrid, aes(x = J, y = I, z = V, color = V))
  p <- p + geom_tile(aes(fill = V))
  p  + scale_fill_manual(values = c("Dead" = "blue", "Alive" = "red"))
}

grid = read.csv(data)
grid2 = subset(grid, grid$T==110)

vi = 0
saveVideo({
for(i in 0:160){
    if(i<=110){
    subgrid = subset(grid, grid$T==i);print(i)}
    else{subgrid = grid2;print(i)}
    grid_ggplot <- grid_to_ggplot(subgrid)
    print(grid_ggplot)
}
}, video.name = outmp4, clean = TRUE)
#system("ffmpeg -i GOL.mp4 -r 8 -filter:v setpts=0.025*PTS GOL_speed.mp4")
system(cmdmp4, intern=TRUE)
#system("ffmpeg -i GOL_speed.mp4 -vf fps=5,scale=450:-1 GOL_speed.gif")
system(cmdgif, intern=TRUE)

#vi = 0
#saveGIF({
#for(i in 0:130){
#    if(i<=110){
#    subgrid = subset(grid, grid$T==i);print(i)}
#    else{subgrid = grid2;print(i)}
#    grid_ggplot2 <- grid_to_ggplot(subgrid)
#    print(grid_ggplot2)
#}
#}, movie.name = "GOL.gif", clean = TRUE)
#system("ffmpeg -i GOL.gif -r 5 -filter:v setpts=0.25*PTS GOL2.gif")


#***********************************************************************
#ani.options("convert")

#saveGIF({
#  for (i in 1:10) plot(runif(10), ylim = 0:1)
#})


#game_grids <- game_of_life(size = 5, num_reps = 2, prob = c(0.1, 0.9))
#print(game_grids)
#grid_ggplot <- lapply(game_grids, grid_to_ggplot)
#saveGIF(lapply(grid_ggplot, print), movie.name="ani.gif", clean = TRUE)
#************************************************************************