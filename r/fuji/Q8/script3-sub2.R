#setwd("/Users/ukohank517/workspace/rstudio/fuji/Q8")  # csv‚ÌêŠ‚ğİ’è

res60M1[which(res60M1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res60M1[which(res60M1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res60M1[which(res60M1 == "‚¢‚¢")] <- "—Ç‚¢"
res60M.t2 <- table(res60M1)
res60M.t3 <- res60M.t2[names(res60M.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res50F1[which(res50F1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res50F1[which(res50F1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res50F1[which(res50F1 == "‚¢‚¢")] <- "—Ç‚¢"
res50F.t2 <- table(res50F1)
res50F.t3 <- res50F.t2[names(res50F.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res50M1[which(res50M1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res50M1[which(res50M1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res50M1[which(res50M1 == "‚¢‚¢")] <- "—Ç‚¢"
res50M.t2 <- table(res50M1)
res50M.t3 <- res50M.t2[names(res50M.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res40F1[which(res40F1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res40F1[which(res40F1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res40F1[which(res40F1 == "‚¢‚¢")] <- "—Ç‚¢"
res40F.t2 <- table(res40F1)
res40F.t3 <- res40F.t2[names(res40F.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res40M1[which(res40M1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res40M1[which(res40M1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res40M1[which(res40M1 == "‚¢‚¢")] <- "—Ç‚¢"
res40M.t2 <- table(res40M1)
res40M.t3 <- res40M.t2[names(res40M.t2) %in%  okinawa.lab] #row.names(okinawa.t)]

res30F1[which(res30F1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res30F1[which(res30F1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res30F1[which(res30F1 == "‚¢‚¢")] <- "—Ç‚¢"
res30F.t2 <- table(res30F1)
res30F.t3 <- res30F.t2[names(res30F.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res30M1[which(res30M1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res30M1[which(res30M1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res30M1[which(res30M1 == "‚¢‚¢")] <- "—Ç‚¢"
res30M.t2 <- table(res30M1)
res30M.t3 <- res30M.t2[names(res30M.t2) %in% okinawa.lab] # row.names(okinawa.t)]


res20F1[which(res20F1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res20F1[which(res20F1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res20F1[which(res20F1 == "‚¢‚¢")] <- "—Ç‚¢"
res20F.t2 <- table(res20F1)
res20F.t3 <- res20F.t2[names(res20F.t2) %in%  okinawa.lab] #row.names(okinawa.t)]


res20M1[which(res20M1 == "‚«‚ê‚¢")] <- "”ü‚µ‚¢"
res20M1[which(res20M1 == "—~‚µ‚¢")] <- "‚Ù‚µ‚¢"
res20M1[which(res20M1 == "‚¢‚¢")] <- "—Ç‚¢"
res20M.t2 <- table(res20M1)
res20M.t3 <- res20M.t2[names(res20M.t2) %in%  okinawa.lab] #row.names(okinawa.t)]

#setwd("/Users/ukohank517")              # ‚¨‚Ü‚¶‚È‚¢

