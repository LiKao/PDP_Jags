### Initialization of a single network

rm(list = ls())

library(R2jags)

# set max.print to something very large, so we can get
# the full results
options(max.print=1000000)

# We have to explicitly load the Pdp module
load.module("Pdp")

modelstring <- "
data {
  # Number of participants
  N <- 2
  # Number of trial types
  M <- 3

  # We name our nodes, so the code becomes more readable
  Cue1Node    <- 1
  Cue2Node    <- 2
  Cue3Node    <- 3
  Cue4Node    <- 4
  Option1Node <- 5
  Option2Node <- 6

  # Three different networks with different validities (same structure)
  val[1,1] <- 0.90
  val[2,1] <- 0.85
  val[3,1] <- 0.80
  val[4,1] <- 0.75

  val[1,2] <- 0.90
  val[2,2] <- 0.80
  val[3,2] <- 0.70
  val[4,2] <- 0.60

  val[1,3] <- 0.85
  val[2,3] <- 0.65
  val[3,3] <- 0.60
  val[4,3] <- 0.55

  # Network patterns

  # Option 1
  ptrn[1,1,1] <-  1
  ptrn[1,2,1] <- -1
  ptrn[1,3,1] <-  1
  ptrn[1,4,1] <- -1

  # Option 2
  ptrn[2,1,1] <- -1
  ptrn[2,2,1] <-  1
  ptrn[2,3,1] <- -1
  ptrn[2,4,1] <-  1

  # Option 1
  ptrn[1,1,2] <-  1
  ptrn[1,2,2] <- -1
  ptrn[1,3,2] <-  1
  ptrn[1,4,2] <- -1

  # Option 2
  ptrn[2,1,2] <- -1
  ptrn[2,2,2] <-  1
  ptrn[2,3,2] <- -1
  ptrn[2,4,2] <-  1

  # Option 1
  ptrn[1,1,3] <-  1
  ptrn[1,2,3] <- -1
  ptrn[1,3,3] <-  1
  ptrn[1,4,3] <- -1

  # Option 2
  ptrn[2,1,3] <- -1
  ptrn[2,2,3] <-  1
  ptrn[2,3,3] <- -1
  ptrn[2,4,3] <-  1


  net <-
     BiLink(1, Cue1Node, Option1Node,  BiLink(2, Cue1Node, Option2Node, # BiLink creates a bidirection link between two nodes
     BiLink(3, Cue2Node, Option1Node,  BiLink(4, Cue2Node, Option2Node, # BiLink creates a bidirection link between two nodes
     BiLink(5, Cue3Node, Option1Node,  BiLink(6, Cue3Node, Option2Node, # BiLink creates a bidirection link between two nodes
     BiLink(7, Cue4Node, Option1Node,  BiLink(8, Cue4Node, Option2Node, # BiLink creates a bidirection link between two nodes
     BiLink(9, Option1Node, Option2Node,                                # BiLink creates a bidirection link between two nodes
     BiasInput(10, Cue1Node,                                             # Adds an input from Bias or GeneralActivation node
     BiasInput(11, Cue2Node,                                             # Adds an input from Bias or GeneralActivation node
     BiasInput(12, Cue3Node,                                             # Adds an input from Bias or GeneralActivation node
     BiasInput(13, Cue4Node,                                             # Adds an input from Bias or GeneralActivation node
     MakeNetwork(6))))))))))))))                                         # Initial network to be passed to all construction function
     # Ensure all parentheses are closed!

}
model {
  # Two participants with different parameters
  for(n in 1:N) {
    p[n] ~ dlnorm(log(1.5),10)
    f[n] ~ dlnorm(log(0.2),10)
    c[n] ~ dlnorm(log(0.01),10)

    # We need to duplicate the parameters to have the correct structure
    for(i in 1:M) {
      fi[i,n] <- f[n]

      for(j in 1:4) {
        for(k in 1:2) {
          ptrni[k,j,i,n] <- c[n]*ptrn[k,j,i]
        }
      }
    }
  }

  m <- Net2Mat(
    net,
    ptrni[1,1,,], ptrni[2,1,,],
    ptrni[1,2,,], ptrni[2,2,,],
    ptrni[1,3,,], ptrni[2,3,,],
    ptrni[1,4,,], ptrni[2,4,,],
    -fi,
    tau(val[1,],p), tau(val[2,],p), tau(val[3,],p), tau(val[4,],p) )
}"


jres <- jags(data=list(), model.file = textConnection(modelstring), DIC = F, parameters.to.save = c("p","f","c","m"), n.burnin = 50, n.iter = 100, n.chains = 1)
jres