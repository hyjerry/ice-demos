//
// Copyright (c) ZeroC, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <objc/Ice/Ice.h>

@protocol DemoLibraryPrx;
@protocol ICECommunicator;
@protocol DemoBookQueryResultPrx;
@protocol GLACIER2RouterPrx;

@class DemoBookDescription;
@class RentController;
@class EditController;
@class SavingController;

@interface LibraryController : NSWindowController
{
    IBOutlet NSTableView* queryTable;
    IBOutlet NSSearchField* searchField;
    IBOutlet NSView* detailView;

    IBOutlet NSTextField* isbnField;
    IBOutlet NSTextView* titleField;
    IBOutlet NSTextField* renterField;
    IBOutlet NSTableView* authorsTable;

    IBOutlet NSToolbar* toolbar;
    IBOutlet NSProgressIndicator* searchIndicator;

    RentController* rentController;
    EditController* editController;
    SavingController* savingController;

    id<ICECommunicator> communicator;
    id session;
    id<DemoLibraryPrx> library;
    id<GLACIER2RouterPrx> router;

    // The current query.
    id<DemoBookQueryResultPrx> query;
    NSMutableArray* books;
    int rowsQueried;
    int nrows;
    NSInteger searchType; // Equivalent to the tag of the menu item.

    DemoBookDescription* selection;
    DemoBookDescription* updated;
}

-(id)initWithCommunicator:(id<ICECommunicator>)communicator
                  session:(id)session
                   router:(id<GLACIER2RouterPrx>)router
                  library:(id<DemoLibraryPrx>)library;

-(void)destroySession;

-(void)add:(id)sender;
-(void)remove:(id)sender;

-(void)setSearchType:(id)sender;
-(void)search:(id)sender;

-(void)logout:(id)sender;
-(void)edit:(id)sender;
-(void)rentBook:(id)sender;
-(void)returnBook:(id)sender;

@end
