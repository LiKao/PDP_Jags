### Initialization of a single network

rm(list = ls())

library(R2jags)
library(tidyverse)

load.module("Pdp")

# set max.print to something very large, so we can get
# the full results
options(max.print=1000000)

get.samples <- function(mcmc,var,...) {
  idx <- c(...)
  if(!is.null(idx)) {
    return( mcmc[,var %idx% idx] )
  }
  return( mcmc[,var] )
}

n.burn   <-   500
n.iter   <-   2000
n.thin   <-     1
n.chains <-     2

# Load trial data
df.trials  <- read.csv("trials.csv")
df.choices <- read.csv("choices.csv")

jData <- list(
  validities = df.trials %>% select(val1:val6) %>% as.matrix() %>% t(),
  ACue       = df.trials %>% select(Acue1:Acue6) %>% as.matrix() %>% t(),
  BCue       = df.trials %>% select(Bcue1:Bcue6) %>% as.matrix() %>% t(),
  trial      = df.choices$taskNo,
  choices    = df.choices$optionAchosen
)

start <- Sys.time()
jres <- jags(data=jData, model.file = "estimation.bugs", parameters.to.save = c("f","p","c","lambda"),
                      n.iter = n.iter, n.burnin = n.burn, n.thin = n.thin, n.chains = n.chains)
#                      export_obj_names=c("n.iter","n.burn","n.thin","n.chains"),
#                      jags.module = c("glm","dic","Pdp"))
jres
end <- Sys.time()
print(end - start)

samples <- jres %>% as.mcmc() %>% as.matrix()
