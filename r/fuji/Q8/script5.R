library(RMeCab)                     # �ǂݎ��
setwd("/Users/ukohank517/workspace/rstudio/fuji/Q8")  # csv�̏ꏊ��ݒ�

# ���_:
# �E��F, ����M���W�܂��Ă�B
# �}�̉��ɂ�20,30�オ�W�����Ă�
# ���_�̋߂��̏��u���R�A�����A�X�A�C�v�������̂Ȃ���ʂȈӌ�


# 20F�̋߂��Ɂu�����A�k���v-> �Ⴂ�����̍D�݂��낤



# 50, 60��̏����̋߂��ɂ́u�z�e���A���ԁv���v���b�g����Ă���B
for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "����" & !is.na(okinawa$Age[i]) & ( okinawa$Age[i] == "�U�O��" |  okinawa$Age[i] == "�T�O��")){
    if(any( res[[i]] %in% c( "����", "�z�e��")  )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}
# �����̏������H����΂�낵�����낤�B


for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "�j��" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "�T�O��" ){
    if(any( res[[i]] %in%  "���H"  )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}




for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "�j��" & !is.na(okinawa$Age[i]) & (okinawa$Age[i] == "�U�O��" )){
    #   print(i)
    if(any( res[[i]] %in%  "�K�v" )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}

for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "�j��" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "�Q�O��" ){
    #   print(i)
    if(any( res[[i]] %in%  "����"  | res[[i]] %in%  "�[��" )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}



setwd("/Users/ukohank517")              # ���܂��Ȃ�
