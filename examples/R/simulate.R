### Initialization of a single network

rm(list = ls())

library(R2jags)
library(tidyverse)

get.samples <- function(mcmc,var,...) {
  idx <- c(...)
  if(!is.null(idx)) {
    return( mcmc[,var %idx% idx] )
  }
  return( mcmc[,var] )
}

# We have to explicitly load the Pdp module
load.module("Pdp")

modelstring <- "
data {
  # We name our nodes, so the code becomes more readable
  Cue1Node    <- 1
  Cue2Node    <- 2
  Cue3Node    <- 3
  Cue4Node    <- 4
  Option1Node <- 5
  Option2Node <- 6

  val[1] <- 0.90
  val[2] <- 0.85
  val[3] <- 0.80
  val[4] <- 0.75

  net <-
       BiLink(1, Cue1Node, Option1Node,  BiLink(2, Cue1Node, Option2Node, # BiLink creates a bidirection link between two nodes
       BiLink(2, Cue2Node, Option1Node,  BiLink(1, Cue2Node, Option2Node, # BiLink creates a bidirection link between two nodes
       BiLink(1, Cue3Node, Option1Node,  BiLink(2, Cue3Node, Option2Node, # BiLink creates a bidirection link between two nodes
       BiLink(2, Cue4Node, Option1Node,  BiLink(1, Cue4Node, Option2Node, # BiLink creates a bidirection link between two nodes
       BiLink(3, Option1Node, Option2Node,                                # BiLink creates a bidirection link between two nodes
       BiasInput(4, Cue1Node,                                             # Adds an input from Bias or GeneralActivation node
       BiasInput(5, Cue2Node,                                             # Adds an input from Bias or GeneralActivation node
       BiasInput(6, Cue3Node,                                             # Adds an input from Bias or GeneralActivation node
       BiasInput(7, Cue4Node,                                             # Adds an input from Bias or GeneralActivation node
       MakeNetwork(6))))))))))))))                                        # Initial network to be passed to all construction function
       # Ensure all parentheses are closed!
}
model {
  # Random network parameters
  f ~ dlnorm(log(0.2),10)
  c ~ dlnorm(log(0.01),10)
  p ~ dlnorm(log(1.5),10)

  finact <- Simulate0(net, 0.1, c, -c, -f, tau(val[1],p), tau(val[2],p), tau(val[3],p), tau(val[4],p))
  p.o1 <- exp(finact[5])/(exp(finact[5]) + exp(finact[6]))
}"


jres <- jags(data=list(), model.file = textConnection(modelstring), DIC = F, parameters.to.save = c("finact","f","c","p","p.o1"))
jres

samples <- jres %>% as.mcmc() %>% as.matrix()
