proj: 	$(PLATFORM_CONFIG_FILE) $(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@echo $($(quiet_)link)
	$(LD) $(LDFLAGS) -o $(PROJ_NAME).elf $(OBJS) $(LIBS)
