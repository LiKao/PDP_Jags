### Initialization of a single network

rm(list = ls())

library(R2jags)

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
}
model {
  # Random network parameters
  f ~ dlnorm(log(0.2),10)
  c ~ dlnorm(log(0.01),10)
  p ~ dlnorm(log(1.5),10)

  net <-
         BiLink(Cue1Node, Option1Node,  c, BiLink(Cue1Node, Option2Node, -c, # BiLink creates a bidirection link between two nodes
         BiLink(Cue2Node, Option1Node, -c, BiLink(Cue2Node, Option2Node,  c, # BiLink creates a bidirection link between two nodes
         BiLink(Cue3Node, Option1Node,  c, BiLink(Cue3Node, Option2Node, -c, # BiLink creates a bidirection link between two nodes
         BiLink(Cue4Node, Option1Node, -c, BiLink(Cue4Node, Option2Node,  c, # BiLink creates a bidirection link between two nodes
         BiLink(Option1Node, Option2Node, -f,                                # BiLink creates a bidirection link between two nodes
         BiasInput(Cue1Node, tau(val[1],p),                                  # Adds an input from Bias or GeneralActivation node
         BiasInput(Cue2Node, tau(val[2],p),                                  # Adds an input from Bias or GeneralActivation node
         BiasInput(Cue3Node, tau(val[3],p),                                  # Adds an input from Bias or GeneralActivation node
         BiasInput(Cue4Node, tau(val[4],p),                                  # Adds an input from Bias or GeneralActivation node
         MakeNetwork(6))))))))))))))                                         # Initial network to be passed to all construction function
         # Ensure all parentheses are closed!
}"


jres <- jags(data=list(), model.file = textConnection(modelstring), DIC = F, parameters.to.save = c("net","f","c","p"),)
jres