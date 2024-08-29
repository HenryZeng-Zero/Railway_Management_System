prefix = gResource

$(prefix).c: $(prefix).h
	glib-compile-resources --generate-source $(prefix).xml

$(prefix).h: $(prefix).xml
	glib-compile-resources --generate-header $(prefix).xml

clean:
	rm -f $(prefix).o $(prefix).c $(prefix).h

clean-ui:
	rm -f *.ui